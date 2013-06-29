/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include "config.h"
#include "cmos.h"
#include "pit.h"
#include "pic.h"
#include "igates.h"
#include "systables.h"
#include "task.h"
#include "vconsole.h"

u32 exIdt;
u32 exGdt;


















void iniz( u32 idt, u32 gdt )
{
  exIdt = idt;
  exGdt = gdt;

  inizVConsole();

  // Configuring PIT (programmable interval timer)
  // PIT Channel 0 - IRQ0 - scheduler
  INIT_PIT( PIT_CONFIG_CH0 | PIT_MODE3 | PIT_BIN | PIT_READ_LHB );
  SET_PIT( PIT_DIVIDER(20), PIT_CH0 );

  // Set 24-hour mode
  // Set binary data format
  wrcmos( rdcmos(CMOS_RTC_STATUSB) | 0x4 | 0x2, CMOS_RTC_STATUSB );

  // If battery is low...
  if( !(rdcmos(CMOS_RTC_STATUSD) & 0x80) )
    vsprint("warning: cmos battery is low\n");

  // Configuring PIC and interrupts
  setTrapGate( &onIRQ0, IRQ(0) );
  setTrapGate( &onIRQ1, IRQ(1) );
  SET_PIC_MASK( ~0x0300 );

  // Configuring scheduler
  inizTask( &xtask, TSS_ENTRY(0) );
  LTR( xtask.uid );
  currentTask = &xtask;
  currentTask->next = currentTask;
};
