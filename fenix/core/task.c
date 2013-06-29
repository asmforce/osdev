/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_TASK_C
#define FENIX_TASK_C

#include "../include/aliases.h"
#include "../include/asm.h"
#include "../include/io.h"
#include "../include/systables.h"
#include "../include/task.h"

Task  task0;
Task *current;



void doOnTimer( u32 eip, u32 eflags )
{
  Task *next = current->next;

  searchNextTask:
    if( next == current )  return;
    if( next->state == TASK_STATE_ACTIVE )
      goto switchToSelected;
    next = next->next;
  goto searchNextTask;
  switchToSelected:


  current->tss.eip = eip;
  current->tss.ebp += 12; // адрес возврата в 'onTimer', затем адрес возврата в точку, где был eip до прерывания таймера, и eflags
  current->tss.esp += 12;
  current->tss.eflags = eflags;

  static struct  { u32 effective, selector; }  address;


  current = next; // Now is currrent
  address.selector = current->uid;

  ASM( "ljmp *%0" :: "m" (address) ); // Switch to changed
};


void onTaskFault( u32 errorCode )
{
  if( current == &task0 )
  {
    prints( "[Fatal:KernelFault]" );
    wrio8( rdio8(0x70) | 0x80, 0x70 );     // Mask NMI
    HLT();
  } else {
    current->errorCode = errorCode;
    current->state = TASK_STATE_FAILED;
    ASM("int $0x20"); // Call scheduler
  };
};


static void registerTask( Task *task )
{
  static u32 ordinal = 3;

  gdtable[ordinal].a16 = sizeof(Task) & 0x00FFFF - 1;      // Считается, что лимит не больше 64 K
  gdtable[ordinal].f8  = 0x89;
  gdtable[ordinal].g8  = 0x00;
  gdtable[ordinal].b16 = (u32) task & 0x0000FFFF;          // Младшее слово адреса базы
  gdtable[ordinal].e8  = ((u32) task & 0x00FF0000) >> 16;  // Младший байт старшего слова
  gdtable[ordinal].h8  = ((u32) task & 0xFF000000) >> 24;  // Старший байт старшего слова

  task->uid = ordinal << 3;

  ++ordinal;

  task->errorCode = TASK_ERROR_NONE;
  task->exitCode = TASK_EXIT_SUCCESS;
  task->switchTimes = 0;
  task->signal = 0;
  task->state = TASK_STATE_ACTIVE;
};


void createTask( Task *task, u32 entry, u32 stack )
{
  registerTask( task );

  task->tss.eip = entry;

  task->tss.es = task->tss.ds = task->tss.ss = task->tss.fs = task->tss.gs = 0x10;
  task->tss.cs = 0x08;

  task->tss.ebp = task->tss.esp = stack;
  task->tss.eflags = 0x200; // IF=1
  task->tss.cr3 = 0;
  task->tss.iomap = sizeof(Tss);
  task->tss.debug = 0;

  task->next = current->next;
  current->next = task;
};


void configureScheduler()
{
  task0.next = &task0;
  current = &task0;

  registerTask( &task0 );
  ASM("ltr %%ax" :: "a" (task0.uid) );
};

#endif
