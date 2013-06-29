/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_STRING_H
#define FENIX_STRING_H

#include "aliases.h"

static inline u32 strlen( const tchar *cs )
{
  u32 n;
  ASM("cld \n\t"
      "repne\tscasb \n\t"
      "notl %%ecx \n\t"
      "decl %%ecx \n\t"
      "decl %%ecx \n\t"
      : "=c" (n)
      : "a" (0x00), "c" (0xFFFFFFFF), "D"  (cs) );
  return n;
};

static inline tchar *strcpy( tchar *to, const tchar *from )
{
  ASM("cld \n\t"
      "loopmark: \n\t"
      "lodsb \n\t"
      "stosb \n\t"
      "test %%al, %%al \n\t"
      "jnz loopmark\n\t"
      ::"S" (from), "D" (to), "c" (0xFFFFFFFF) );
  return to;
};

static inline tchar *strncpy( tchar *to, const tchar *from, u32 n )
{
  ASM("cld \n\t"
      "loopmark: \n\t"
      "lodsb \n\t"
      "stosb \n\t"
      "test %%al, %%al \n\t"
      "jnz loopmark\n\t"
      ::"S" (from), "D" (to), "c" (n) );
  return to;
};

const tchar *u32ToString( u32 num, u8 radix );
const tchar *i32ToString( i32 num, u8 radix );


#endif
