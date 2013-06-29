/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_TASK_H
#define FENIX_TASK_H

#include "aliases.h"

/**
 * Task::state
 * Task state:
 * TASK_STATE_EXITED - normal exit
 * TASK_STATE_ACTIVE - currently is executing
 * TASK_STATE_HALTED - temporarily paused
 * TASK_STATE_FAILED - stoped by exception
**/
#define TASK_STATE_EXITED 0x00
#define TASK_STATE_ACTIVE 0x01
#define TASK_STATE_HALTED 0x02
#define TASK_STATE_FAILED 0x03


/**
 * Task::exitCode
 * Exit code:
 * - uses for returning from task's main function
 * TASK_EXIT_SUCCESS - normal exit
 * TASK_EXIT_FAILED - some error occured
**/
#define TASK_EXIT_SUCCESS 0x00
#define TASK_EXIT_FAILED  0x01


/**
 * Task::errorCode
 * Error code:
 * - code of occured exception
 * TASK_ERROR_NONE - no exception. default value
**/
#define TASK_ERROR_NONE                0x00
#define TASK_ERROR_DIVIDE              0x01
#define TASK_ERROR_DEBUG               0x02
#define TASK_ERROR_NMI                 0x03
#define TASK_ERROR_BREAKPOINT          0x04
#define TASK_ERROR_OVERFLOW            0x05
#define TASK_ERROR_BOUNDS_EXCEEDED     0x06
#define TASK_ERROR_INVALID_OPCODE      0x07
#define TASK_ERROR_NO_X87              0x08
#define TASK_ERROR_DOUBLE_FAULT        0x09
#define TASK_ERROR_X87_OVERRUN         0x0A
#define TASK_ERROR_INVALID_TSS         0x0B
#define TASK_ERROR_SEGMENT_NOT_PRESENT 0x0C
#define TASK_ERROR_STACK_SEGMENT_FAULT 0x0D
#define TASK_ERROR_GENERAL_PROTECTION  0x0E
#define TASK_ERROR_PAGE_FAULT          0x0F
#define TASK_ERROR_RESERVED            0x10
#define TASK_ERROR_X87_FAULT           0x11
#define TASK_ERROR_ALIGNMENT_CHECK     0x12



typedef struct
{
  u16 link;
  unsigned:16;

  u32 esp0;
  u16 ss0;
  unsigned:16;

  u32 esp1;
  u16 ss1;
  unsigned:16;

  u32 esp2;
  u16 ss2;
  unsigned:16;

  u32 cr3;
  u32 eip;
  u32 eflags;

  u32 eax;
  u32 ecx;
  u32 edx;
  u32 ebx;

  u32 esp;
  u32 ebp;
  u32 esi;
  u32 edi;

  u16 es;
  unsigned:16;
  u16 cs;
  unsigned:16;
  u16 ss;
  unsigned:16;
  u16 ds;
  unsigned:16;
  u16 fs;
  unsigned:16;
  u16 gs;
  unsigned:16;

  u16 ldtr;
  unsigned:16;

  unsigned debug:1;
  unsigned:15;
  u16 iomap;
} Tss;


typedef struct
{
  u32 cwd;
  u32 swd;
  u32 twd;
  u32 fip;
  u32 fcs;
  u32 foo;
  u32 fos;
  // 8 regs, 10 bytes per reg
  u8  space[80];
} ContextI387;


typedef struct Task
{
  Tss          tss;
  ContextI387  i387;

  /*
  ContextI387 coproc;
  dump( (u32) &coproc, sizeof(coproc) );
  asm( "fnsave %0" :: "m" (coproc) );
  dump( (u32) &coproc, sizeof(coproc) );
  asm( "frstor %0" :: "m" (coproc) );
  */

  struct Task *next;

  u16          uid;
  u32          errorCode;
  u32          exitCode;
  u32          switchTimes;
  u32          signal;
  u32          state;
} Task;



extern Task  task0;
extern Task *current;



void onTimer();

ASM("_onTimer:          ;"    // IRQ0
    "call _doOnTimer    ;"
    "sti                ;"
    "iret               ;");

void configureScheduler();
void onTaskFault( u32 errorCode );
void createTask( Task *task, u32 entry, u32 stack );


#endif
