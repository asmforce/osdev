/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_IO_H
#define FENIX_IO_H

#include "aliases.h"

static void inline wrio8( u8 value, u16 port )
{
  ASM volatile ( "outb %%al, %%dx" :: "a"(value),"d"( port) );
};

static void inline wrio16( u16 value, u16 port )
{
  ASM volatile ( "outw %%ax, %%dx" :: "a"(value),"d"(port) );
};

static void inline wrio32( u32 value, u16 port )
{
  ASM volatile ( "outl %%eax, %%dx" :: "a" (value), "d" (port) );
};



static u8 inline rdio8( u16 port )
{
  u8 value;
  ASM volatile ( "inb %%dx, %%al" : "=a" (value) : "d" (port) );
  return value;
};

static u16 inline rdio16( u16 port )
{
  u16 value;
  ASM volatile ( "inw %%dx, %%ax" : "=a" (value) : "d" (port) );
  return value;
};

static u32 inline rdio32( u16 port )
{
  u32 value;
  ASM volatile ( "inl %%dx, %%eax" : "=a" (value) : "d" (port) );
  return value;
};

#endif
