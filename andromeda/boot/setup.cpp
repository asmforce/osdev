/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include <aliases.hpp>
#include <console.hpp>
#include <io.hpp>
#include <systables.hpp>
#include <pic.hpp>
#include <ps2.hpp>


/*
void echo( bool status )  {
  console::o( status ? "true " : "false " );
};
*/


#define CLI() GASM("CLI")
#define STI() GASM("STI")
#define NOP() GASM("NOP")
#define HLT() GASM("HLT")






CMANGLE void onIRQ0();
GASM(
  "_onIRQ0:           ;"
  "pusha              ;"
  "call _doOnIRQ0     ;"
  "popa               ;"
  "iret               ;"
);

CMANGLE void doOnIRQ0()
{
  console::putc( 't' );
};


CMANGLE void onIRQ12();
GASM(
  "_onIRQ12:          ;"
  "pusha              ;"
  "call _doOnIRQ12    ;"
  "popa               ;"
  "mov $0x20, %al     ;"
  "out %al, $0x20     ;"
  "out %al, $0xA0     ;"
  "iret               ;"
);

CMANGLE void doOnIRQ12()
{
  u8 buttons;
  i8 dx, dy;

  buttons = io::i8( 0x60 );
  dx = io::i8( 0x60 );
  dy = io::i8( 0x60 );

  u32 r,c;

  r = console::line();
  c = console::column();
  console::pos( 0, 0 );
  console::putcs( "m(" );
  console::putcs( dx == 0 ? "N" : dx < 0 ? "<" : ">" );
  console::putcs( dy == 0 ? "N" : dy < 0 ? "." : "'" );
  console::putc( ')' );
  console::pos( r, c );
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
  console::putc( 'k' );

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

  if( scancode == 1 )  {
    // disabled by-default
    static bool enabled = false;

    if( enabled )
      MOUSE(CLI);
    else
      MOUSE(STI);

    enabled = !enabled;
  };
};



namespace ps2
{
  void waitBufferFreing()  {
    while( io::i8(0x64) & 0x2 );
  }

  void waitDataReady()  {
    while( !(io::i8(0x64) & 0x1) );
  }
}




CMANGLE void setup( void *idtable, void *gdtable )
{
  // system gates, system descriptors initialization
  systables::setup( idtable, gdtable );

  // system gates setup
  sysgates::setup( IRQ(0), SYSSEG(CODE), (void*) &onIRQ0, SYSGATE(INT,32), RING(0) );
  sysgates::setup( IRQ(1), SYSSEG(CODE), (void*) &onIRQ1, SYSGATE(INT,32), RING(0) );
  sysgates::setup( IRQ(12), SYSSEG(CODE), (void*) &onIRQ12, SYSGATE(INT,32), RING(0) );

  // setup console subsystem, clear screen
  console::setup();
  console::putcs( "[andromeda:setup execution]" );
  console::newline();
  console::putc( '*' );
  console::newline();
  console::newline();

  // unmask IRQ0 and IRQ1 (master pic)
  pic::unmask( 0x3 );


  ps2::mouse::setup( 100000 );

  u8 data;
  ps2::waitBufferFreing();
  io::o8( 0x64, 0x20 );
  ps2::waitDataReady();
  data = io::i8(0x60);
  ps2::waitBufferFreing();
  io::o8( 0x64, 0x60 );
  ps2::waitBufferFreing();
  io::o8( 0x60, data | 0x02 & 0xDF );
  ps2::waitBufferFreing();
  io::o8( 0x64, 0xD4 );
  ps2::waitBufferFreing();
  io::o8( 0x60, 0xF4 );
};

CMANGLE void cppmain()
{
  STI();
  for(;;)  {
    console::putc( '.' );
    HLT();
  };
};
