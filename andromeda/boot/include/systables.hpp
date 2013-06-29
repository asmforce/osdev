/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef ANDROMEDA_SYSTABLES_HPP
#define ANDROMEDA_SYSTABLES_HPP

#include <aliases.hpp>

// IDT: system gate's type macros
#define SYSGATE_TASK32 0xD
#define SYSGATE_INT32  0xE
#define SYSGATE_TRAP32 0xF

#define SYSGATE_TASK16 0x5
#define SYSGATE_INT16  0x6
#define SYSGATE_TRAP16 0x7

#define SYSGATE( TYPE, D )  (SYSGATE_ ## TYPE ## D)

#define IRQ( i )  ((i) + 0x20)
#define INT( i )           \
GASM("mov %%al, 1f     ;"  \
     ".byte 0xCD       ;"  \
     "1:               ;"  \
     ".byte 0x00       ;"  \
     :: "a" (i) )


// DPL
#define RING(x)  (x)

// GDT system entries
#define SYSSEG_CODE  (1<<3)
#define SYSSEG_DATA  (2<<3)
// !!! Currently doesn't exists
//#define SYSSEG_STACK (3<<3)
#define SYSSEG(SEG)  (SYSSEG_ ## SEG)


// GDT: system dsc's type macros
// Code group
#define SYSDSC_CODE     0x8
#define SYSDSC_READABLE 0x2
#define SYSDSC_SUBSEG   0x4
// Read-only bit (convention)
#define SYSDSC_ACCESSED 0x1

// Data group
#define SYSDSC_DATA     0x0
#define SYSDSC_WRITABLE 0x2
#define SYSDSC_STACK    0x4

#define SYSDSC1(DSC)        (SYSDSC_ ## DSC)
#define SYSDSC2(DSC,F1)     (SYSDSC_ ## DSC | SYSDSC_ ## F1)
#define SYSDSC3(DSC,F1,F2)  (SYSDSC_ ## DSC | SYSDSC_ ## F1 | SYSDSC_ ## F2)

/* Correct combinations
SYSDSC1(CODE)                  // Executable-only code segment
SYSDSC2(CODE,READABLE)         // Executable and readable code segment
SYSDSC2(CODE,SUBSEG)           // Subordinate code segment
SYSDSC3(CODE,READABLE,SUBSEG)  // Executable and readable subordinate code segment


SYSDSC1(DATA)                  // Read-only data segment
SYSDSC2(DATA,WRITABLE)         // Readable and writable data segment
SYSDSC2(DATA,STACK)            // Read-only stack segment
SYSDSC3(DATA,WRITABLE,STACK)   // Readable and writable stack segment
*/

namespace systables  {
  static void setup( void *idtable, void *gdtable );
}; // namespace systables

namespace sysgates
{
  struct gate  {
    u16 entryL;
    u16 selector;
    u8  zero1;
    u8  type:4;
    u8  zero2:1;
    u8  dpl:2;
    u8  present:1;
    u16 entryH;
  } PACKED; // struct gate

  // interrupt descriptor table
  static gate *table;

  // sets up the gate
  static void setup( u8 index, u16 sysseg, void *function, u8 type, u8 ring );
}; // namespace sysgates

namespace sysdscs
{
  struct dsc  {
    u16 sizeL;
    u16 baseL;
    u8  baseM;
    u8  type:4;
    u8  system:1;
    u8  dpl:2;
    u8  present:1;
    u8  sizeH:4;
    u8  zero:2;
    u8  db:1;
    u8  granularity:1;
    u8  baseH;
  } PACKED; // struct dsc

  // general descriptor table
  static dsc *table;
}; // namespace sydscs




void systables::setup( void *idtable, void *gdtable )  {
  sysgates::table = (sysgates::gate*) idtable;
  sysdscs::table = (sysdscs::dsc*) gdtable;
};


void sysgates::setup( u8 index, u16 sysseg, void *function, u8 type, u8 ring )
{
  gate &newgate = table[index];

  u32 entry = (u32) function;
  newgate.entryL = entry & 0xFFFF;
  newgate.entryH = entry << 16u;
  newgate.selector = sysseg;
  newgate.zero1 = 0;
  newgate.type = type & 0x0F;
  newgate.zero2 = 0;
  newgate.dpl = ring & 0x3;
  newgate.present = 1;
};

#endif // ANDROMEDA_SYSTABLES_HPP
