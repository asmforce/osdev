/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_TASK_H
#define XWORKSPACE_TASK_H

#include "config.h"

/**
 * null descriptor,
 * code descriptor,
 * data descriptor,
 * xtask's tss,
 * tss0,
 * tss1,
 * ...
**/
#define GDT_TSS_ENTRY 3
#define TSS_ENTRY( i ) ((i)+GDT_TSS_ENTRY)

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


typedef struct Task
{
  Tss tss;

  u32 uid;
  u32 exitCode;
  u32 state;

  struct Task *next;
} Task;

// Kernel task
extern Task  xtask;
extern Task *currentTask;

extern void inizTask( Task *task, u32 i );
extern void addTask( Task *task, u32 entry, u32 stack );

#endif
