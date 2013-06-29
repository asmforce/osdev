/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_GATES_H
#define FENIX_GATES_H

#include "aliases.h"
#include "systables.h"

#define setIntrGate( handle, index )     setIdtGate( handle, index, 14 )
#define setTrapGate( handle, index )     setIdtGate( handle, index, 15 )

/**
 * Тип шлюза:
 * 0110 - 16-битный шлюз прерывания
 * 0111 - 16-битный шлюз ловушки
 * 1110 - 32-битный шлюз прерывания
 * 1111 - 32-битный шлюз ловушки
**/

static void inline setIdtGate( void (*entry)(), u8 index, u8 type )
{
  IdtDesc *desc = idtable + index;

  desc->a16 = (u32) entry & 0xFFFF;
  desc->d16 = (u32) entry >> 16;

  desc->b16 = 0x8;                  // Системный селектор в GDT, DPL = 0
  desc->e8 = 0x0;                   // Должен быть нулевым
  desc->f8 = 0x80 | (type & 0x0F);  // Бит присутствия, два бита DPL, зарезервированный бит 0, и четыре бита - тип шлюза
};

#endif
