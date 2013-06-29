/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_RAM_H
#define XWORKSPACE_RAM_H

#include "config.h"

static inline i8 ramcmp( const void *ptr0, const void *ptr1, u32 n )
{
  i8 diff;

  ASM("cld                  ;"
      "repe                 ;"
      "cmpsb                ;"
      "dec %%esi            ;"
      "dec %%edi            ;"
      "lodsb                ;"
      "subb (%%edi), %%al   ;"
      : "=a" (diff)
      : "S" (ptr1), "D" (ptr0), "c" (n) );

  return diff;
};


static inline void *ramcpy( void *to, const void *from, u32 n )
{
  ASM("cld                  ;"
      "mov %%ecx, %%ebx     ;"
      "shr $2, %%ecx        ;"
      "and $3, %%ebx        ;"
      "rep                  ;"
      "movsl                ;"
      "mov %%ebx, %%ecx     ;"
      "rep                  ;"
      "movsb                ;"
      :: "S" (from), "D" (to), "c" (n) );

  return to;
};


static inline void *rammov( void *to, const void *from, u32 n )
{
  if ( to < from )
  {
    ASM("cld                  ;"
        "mov %%ecx, %%ebx     ;"
        "shr $2, %%ecx        ;"
        "and $3, %%ebx        ;"
        "rep                  ;"
        "movsl                ;"
        "mov %%ebx, %%ecx     ;"
        "rep                  ;"
        "movsb                ;"
        :: "S" (from), "D" (to), "c" (n) );
  } else {
    ASM("std                  ;"
        "mov %%ecx, %%ebx     ;"
        "shr $2, %%ecx        ;"
        "and $3, %%ebx        ;"
        "rep                  ;"
        "movsl                ;"
        "mov %%ebx, %%ecx     ;"
        "rep                  ;"
        "movsb                ;"
        "cld                  ;"
        :: "S" (from + n - 4), "D" (to + n - 4), "c" (n) );
  };
  return to;
};


static inline void *ramset( void *to, u8 c, u32 n )
{
  ASM("cld                  ;"
      "mov %%ecx, %%ebx     ;"
      "shr $2, %%ecx        ;"
      "and $3, %%ebx        ;"
      "rep                  ;"
      "stosl                ;"
      "mov %%ebx, %%ecx     ;"
      "rep                  ;"
      "stosb                ;"
      :: "D" (to), "a" ((u32) c | (c << 8) | (c << 16) | (c << 24) ), "c" (n) );

  return to;
};

static inline void *ramchr( const void *ptr, tchar c, u32 n )
{
  void *p;

  if( !n )  return 0;

  ASM("cld                  ;"
      "repne                ;"
      "scasb                ;"
      "je 1f                ;"
      "jmp 2f               ;"
      "1:                   ;"
      "  dec %%edi          ;"
      "2:                   ;"
      : "=D" (p)
      : "D" (ptr), "a" (c), "c" (n) );

  return p;
};

#endif
