/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include <xworkspace/config.h>
#include <xworkspace/systables.h>
#include <xworkspace/task.h>
#include <xworkspace/pit.h>

// Kernel task
Task  xtask;
Task *currentTask;




// IRQ0 Is used for [multi-] task scheduling
void doOnIRQ0( u32 eip, u32 eflags )
{  
  struct  { u32 effective, selector; }  address;
  Task *task = currentTask->next;

  for(;;)
  {
    if( task == currentTask )  return;
    if( task->state == TASK_STATE_ACTIVE )
      break;
    task = task->next;
  };

  currentTask = task;
  address.selector = currentTask->uid;

  ASM( "ljmp *%0" :: "m" (address) );
};




void inizTask( Task *task, u32 i )
{
  GdtDesc *gdt = (GdtDesc*) exGdt;

  gdt[i].a16 = sizeof(Task) & 0x00FFFF - 1;      // Считается, что лимит не больше 64 K
  gdt[i].f8  = 0x89;
  gdt[i].g8  = 0x00;
  gdt[i].b16 = (u32) task & 0x0000FFFF;          // Младшее слово адреса базы
  gdt[i].e8  = ((u32) task & 0x00FF0000) >> 16;  // Младший байт старшего слова
  gdt[i].h8  = ((u32) task & 0xFF000000) >> 24;  // Старший байт старшего слова

  task->uid = i << 3;
  task->state = TASK_STATE_ACTIVE;
};


void addTask( Task *task, u32 entry, u32 stack )
{
  task->tss.eip = entry;

  task->tss.es = task->tss.ds = task->tss.ss = task->tss.fs = task->tss.gs = 0x10;
  task->tss.cs = 0x08;

  task->tss.ebp = task->tss.esp = stack;
  task->tss.eflags = 0x200; // IF = 1
  task->tss.cr3 = 0;
  task->tss.iomap = sizeof(Tss);
  task->tss.debug = 0;

  CLI();
  // Insert created task after `currentTask`
  task->next = currentTask->next;
  currentTask->next = task;
  STI();
};
