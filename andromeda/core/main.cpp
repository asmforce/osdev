/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include <boot/mb.hpp>
#include <aliases.hpp>

#include <core/systables.hpp>
#include <core/io.hpp>
#include <core/pic.hpp>
#include <core/console.hpp>

#define CLI() GASM("CLI")
#define STI() GASM("STI")
#define NOP() GASM("NOP")
#define HLT() GASM("HLT")




// provided by `boot.s` code
CMANGLE void *IDT, *GDT;





CMANGLE void onIRQ0();
GASM(
  "_onIRQ0:           ;"
  "pusha              ;"
  "mov $0xFE, %al     ;"
  "out %al, $0x64     ;"
  "1:                 ;"
  "jmp 1b             ;"
  "call _doOnIRQ0     ;"
  "popa               ;"
  "iret               ;"
);

CMANGLE void doOnIRQ0()
{
  console::putc( 'T' );
};

CMANGLE void onIRQ1();
GASM(
  "_onIRQ1:           ;"
  "pusha              ;"
  "call _doOnIRQ1     ;"
  "popa               ;"
  "iret               ;"
);

CMANGLE void doOnIRQ1()
{
  // console::o( '0' );

  u8 scancode;
  GASM(
    "xorl %%eax, %%eax ;"
    "inb $0x60, %%al   ;"
    : "=a" (scancode)
  );
  // console::o( "<$u>", scancode );
  console::putc( 'K' );

  if( scancode == 1 )  {
    // enabled by-default
    static bool enabled = true;

    if( enabled )
    // disable IRQ0
      pic::mask( 0x1 );
    else
    // enable IRQ0
      pic::unmask( 0x1 );

    enabled = !enabled;
  };
};











CMANGLE void setup( u32 magic, multiboot_info_t *mbi )
{
  // setup console subsystem, clear screen
  console::setup();

  // system gates, system descriptors initialization
  systables::setup( IDT, GDT );

  // system gates setup
  sysgates::setup( IRQ(0), SYSSEG(CODE), (void*) &onIRQ0, SYSGATE(INT,32), RING(0) );
  sysgates::setup( IRQ(1), SYSSEG(CODE), (void*) &onIRQ1, SYSGATE(INT,32), RING(0) );
/*
  GASM(
    "xorl %eax, %eax   ;"
    "decl %eax         ;"
    "movl $16, %ecx    ;"
    "movl _IDT, %edi   ;"
    "rep stosb         ;"
  );
*/
  console::putcs( "[andromeda:setup execution]" );
  console::newline();

  if( magic != MULTIBOOT_EAX )  {
    console::putcs( "[error: corrupted multiboot eax magic]" );
    return;
  };
  console::putcs( "[multiboot eax ok]" );
  console::newline();

  //// unmask IRQ0 and IRQ1 (master pic)
  //pic::unmask( 0x3 );

  // unmask IRQ1
  pic::unmask( 0x3 );
  console::putcs( "[unmasking IRQ0,IRQ1]" );
  console::newline();

  // set IF in `eflags`
  console::putcs( "[hlt; waiting for interrupt]" );
  console::newline();
  STI();
  for( ; ; )  {
    HLT();
    console::putc( '/' );
  };
};
