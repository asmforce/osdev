/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_MEMORY_H
#define FENIX_MEMORY_H

#include "aliases.h"



/**
 * 0x00000000-0x000003FF 256 Int Vectors                                   1024
 * 0x00000400-0x000004FF BIOS Data Area                                    256
 * 0x00000500-0x0009FFFF OS Fenix [Core] Area                              654080
 * 0x000A0000-0x000BFFFF Video Memory mode-dependent                       131072
 * 0x000C0000-0x000DFFFF Adapter ROM,RAM                                   131072
 * 0x000E0000-0x000EFFFF System BIOS or Free                               65536
 * 0x000F0000-0x000FFFFF System BIOS                                       65536
 * 0x000FD000-0x000FDFFF ESCD (Extended System Configuration Data) PnP     8192
**/



extern const u32 memoryTotal;

void initRam();




static inline void *ramcpy( void *to, const void *from, u32 n )
{
  ASM("cld\n\t"
      "movl %%ecx, %%ebx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep movsd\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep movsb"
      ::"S" (from), "D" (to), "c" (n) );
  return to;
};

static inline void *ramset( void *to, u8 c, u32 n )
{
  u32 num = c;
  ASM("cld\n\t"
      "movl %%ecx, %%ebx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb"
      ::"D" (to), "a" (num | (num << 8) | (num << 16) | (num << 24)), "c" (n) );
  return to;
};

static inline i8 ramcmp( const void *p1, const void *p2, u32 n )
{
  i8 diff;
  ASM("cld \n\t"
      "repe cmpsb \n\t"
      "decl %%esi \n\t"
      "decl %%edi \n\t"
      "movb (%%edi), %%al \n\t"
      "subb (%%esi), %%al \n\t"
      :"=S" (p2), "=D" (p1), "=a" (diff)
      :"S" (p2), "D" (p1), "c" (n) );
  return diff;
};

#endif
