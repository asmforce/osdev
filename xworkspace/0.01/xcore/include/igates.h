/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_IGATES_H
#define XWORKSPACE_IGATES_H

#include "config.h"
#include "systables.h"

/**
 * Тип шлюза:
 * 0110 - 16-битный шлюз прерывания
 * 0111 - 16-битный шлюз ловушки
 * 1110 - 32-битный шлюз прерывания
 * 1111 - 32-битный шлюз ловушки
**/

#define IRQ( i )  ((i) + 0x20)
#define INT( i )          \
ASM("mov %%al, 1f     ;"  \
    ".byte 0xCD       ;"  \
    "1:               ;"  \
    ".byte 0x00       ;"  \
    :: "a" (i) )

#define setIntrGate( handle, index )     setIdtGate( handle, index, 14 )
#define setTrapGate( handle, index )     setIdtGate( handle, index, 15 )

#define setIdtGate( entry, index, type )   \
ASM("mov %%ax, (%%edi)    ;"               \
    "shr $16, %%eax       ;"               \
    "mov %%ax, 6(%%edi)   ;"               \
    "movw $0x8, 2(%%edi)  ;"               \
    "movb $0, 4(%%edi)    ;"               \
    "mov %%bl, 5(%%edi)   ;"               \
    :: "D" ((u32)exIdt + ((index) << 3)), "a" ((u32)entry), "b" ((u8)(type & 0x0F | 0x80)) );

extern void onIRQ0();
extern void onIRQ1();

extern void doOnIRQ0();
extern void doOnIRQ1( u8 scancode );

#endif
