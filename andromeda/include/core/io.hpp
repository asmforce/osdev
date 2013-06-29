/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef ANDROMEDA_IO_HPP
#define ANDROMEDA_IO_HPP

#include <aliases.hpp>

namespace io
{
  // byte output
  static void INLINE o8( u16 port, u8 value );
  // word output
  static void INLINE o16( u16 port, u16 value );
  // dword output
  static void INLINE o32( u16 port, u32 value );

  // byte input
  static void INLINE i8( u16 port, u8 &value );
  // word input
  static void INLINE i16( u16 port, u16 &value );
  // dword input
  static void INLINE i32( u16 port, u32 &value );

  // byte input
  static u8 INLINE i8( u16 port );
  // word input
  static u16 INLINE i16( u16 port );
  // dword input
  static u32 INLINE i32( u16 port );
}; // namespace io




void io::o8( u16 port, u8 value )  {
  GVASM( "outb %%al, %%dx" :: "a"(value), "d"(port) );
};

void io::o16( u16 port, u16 value )  {
  GVASM( "outw %%ax, %%dx" :: "a"(value), "d"(port) );
};

void io::o32( u16 port, u32 value )  {
  GVASM( "outl %%eax, %%dx" :: "a"(value), "d"(port) );
};


void io::i8( u16 port, u8 &value )  {
  GVASM( "inb %%dx, %%al" : "=a" (value) : "d" (port) );
};

void io::i16( u16 port, u16 &value )  {
  GVASM( "inw %%dx, %%ax" : "=a" (value) : "d" (port) );
};

void io::i32( u16 port, u32 &value )  {
  GVASM( "inl %%dx, %%eax" : "=a" (value) : "d" (port) );
};


u8 io::i8( u16 port )  {
  u8 value;
  GVASM( "inb %%dx, %%al" : "=a" (value) : "d" (port) );
  return value;
};

u16 io::i16( u16 port )  {
  u16 value;
  GVASM( "inw %%dx, %%ax" : "=a" (value) : "d" (port) );
  return value;
};

u32 io::i32( u16 port )  {
  u32 value;
  GVASM( "inl %%dx, %%eax" : "=a" (value) : "d" (port) );
  return value;
};

#endif // ANDROMEDA_IO_HPP
