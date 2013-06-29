/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_PIC_H
#define XWORKSPACE_PIC_H

#include "config.h"

#define GET_PIC_MASK()       \
({                           \
  u16 mask;                  \
  ASM("xor %%eax, %%eax   ;" \
      "mov $0x21, %%dx    ;" \
      "inb %%dx, %%al     ;" \
      "mov %%al, %%ah     ;" \
      "mov $0xA1, %%dx    ;" \
      "inb %%dx, %%al     ;" \
      : "=a" (mask) );       \
  mask;                      \
})


#define SET_PIC_MASK( mask ) \
ASM("mov $0xA1, %%dx      ;" \
    "outb %%al, %%dx      ;" \
    "mov $0x21, %%dx      ;" \
    "mov %%ah, %%al       ;" \
    "outb %%al, %%dx      ;" \
    :: "a" ((u16)mask) )


#define CHANGE_PIC_MASK( mask ) \
ASM("mov $0xA1, %%dx      ;"    \
    "inb %%dx, %%al       ;"    \
    "or %%bl, %%al        ;"    \
    "nop                  ;"    \
    "outb %%al, %%dx      ;"    \
    "mov $0x21, %%dx      ;"    \
    "inb %%dx, %%al       ;"    \
    "or %%bh, %%al        ;"    \
    "nop                  ;"    \
    "outb %%al, %%dx      ;"    \
    :: "b" ((u16)mask) )

#endif
