/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_IO_H
#define XWORKSPACE_IO_H

#include "config.h"

#define WRIO8( byte, port )    ASM volatile ( "out %%al, %%dx" :: "a" (byte), "d" (port) )
#define WRIO16( word, port )   ASM volatile ( "out %%ax, %%dx" :: "a" (word), "d" (port) )
#define WRIO32( dword, port )  ASM volatile ( "out %%eax, %%dx" :: "a" (dword), "d" (port) )

#define RDIO8( byte, port )    ASM volatile ( "in %%dx, %%al" : "=a" (byte) : "d" (port) )
#define RDIO16( word, port )   ASM volatile ( "in %%dx, %%ax" : "=a" (word) : "d" (port) )
#define RDIO32( dword, port )  ASM volatile ( "in %%dx, %%eax" : "=a" (dword) : "d" (port) )


static inline void ALWAYS_INLINE wrio8( u8 value, u16 port )
{
  ASM volatile ( "outb %%al, %%dx" :: "a" (value), "d" (port) );
};

static inline void ALWAYS_INLINE wrio16( u16 value, u16 port )
{
  ASM volatile ( "outw %%ax, %%dx" :: "a" (value), "d" (port) );
};

static inline void ALWAYS_INLINE wrio32( u32 value, u16 port )
{
  ASM volatile ( "outl %%eax, %%dx" :: "a" (value), "d" (port) );
};


static inline u8 ALWAYS_INLINE rdio8( u16 port )
{
  u8 value;
  ASM volatile ( "inb %%dx, %%al" : "=a" (value) : "d" (port) );
  return value;
};

static inline u16 ALWAYS_INLINE rdio16( u16 port )
{
  u16 value;
  ASM volatile ( "inw %%dx, %%ax" : "=a" (value) : "d" (port) );
  return value;
};

static inline u32 ALWAYS_INLINE rdio32( u16 port )
{
  u32 value;
  ASM volatile ( "inl %%dx, %%eax" : "=a" (value) : "d" (port) );
  return value;
};

#endif
