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
 * ��� �����:
 * 0110 - 16-������ ���� ����������
 * 0111 - 16-������ ���� �������
 * 1110 - 32-������ ���� ����������
 * 1111 - 32-������ ���� �������
**/

static void inline setIdtGate( void (*entry)(), u8 index, u8 type )
{
  IdtDesc *desc = idtable + index;

  desc->a16 = (u32) entry & 0xFFFF;
  desc->d16 = (u32) entry >> 16;

  desc->b16 = 0x8;                  // ��������� �������� � GDT, DPL = 0
  desc->e8 = 0x0;                   // ������ ���� �������
  desc->f8 = 0x80 | (type & 0x0F);  // ��� �����������, ��� ���� DPL, ����������������� ��� 0, � ������ ���� - ��� �����
};

#endif
