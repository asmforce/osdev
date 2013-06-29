/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include "config.h"

u32 cslen( const tchar *cs )
{
  u32 n;

  ASM("cld                  ;"
      "xor %%al, %%al       ;"
      "repne                ;"
      "scasb                ;"
      "not %%ecx            ;"
      "dec %%ecx            ;"
      : "=c" (n)
      : "D" (cs), "c" (0xFFFFFFFF) );

  return n;
};


i8 cscmp( const tchar *cs0, const tchar *cs1 )
{
  i8 diff;

  ASM("cld                  ;"
      "1:                   ;"
      "  lodsb              ;"
      "  scasb              ;"
      "  jne 2f             ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      "  xor %%eax, %%eax   ;"
      "  jmp 3f             ;"
      "2:                   ;"
      "  dec %%edi          ;"
      "  subb (%%edi), %%al ;"
      "3:                   ;"
      : "=a" (diff)
      : "D" (cs1), "S" (cs0) );

  return diff;
};


i8 csncmp( const tchar *cs0, const tchar *cs1, u32 n )
{
  i8 diff;

  ASM("cld                  ;"
      "1:                   ;"
      "  lodsb              ;"
      "  scasb              ;"
      "  jne 2f             ;"
      "  dec %%ecx          ;"
      "  jz 2f              ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      "  xor %%eax, %%eax   ;"
      "  jmp 3f             ;"
      "2:                   ;"
      "  dec %%edi          ;"
      "  subb (%%edi), %%al ;"
      "3:                   ;"
      : "=a" (diff)
      : "D" (cs1), "S" (cs0), "c" (n) );

  return diff;
};


tchar *cscpy( tchar *to, const tchar *from )
{
  ASM("cld                  ;"
      "1:                   ;"
      "  lodsb              ;"
      "  stosb              ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      :: "S" (from), "D" (to) );

  return to;
};


tchar *csncpy( tchar *to, const tchar *from, u32 n )
{
  ASM("cld                  ;"
      "1:                   ;"
      "  dec %%ecx          ;"
      "  js 2f              ;"
      "  lodsb              ;"
      "  stosb              ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      "2:                   ;"
      :: "S" (from), "D" (to), "c" (n) );

  return to;
};


tchar *cscat( tchar *to, const tchar *from )
{
  ASM("cld                  ;"
      "xor %%al, %%al       ;"
      "repne                ;"
      "scasb                ;"
      "dec %%edi            ;"
      "1:                   ;"
      "  lodsb              ;"
      "  stosb              ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      :: "S" (from), "D" (to), "c" (0xFFFFFFFF) );

  return to;
};


tchar *csncat( tchar *to, const tchar *from, u32 n )
{
  ASM("cld                  ;"
      "xor %%al, %%al       ;"
      "repne                ;"
      "scasb                ;"
      "dec %%edi            ;"
      "mov %%ebx, %%ecx     ;"
      "1:                   ;"
      "  dec %%ecx          ;"
      "  js 2f              ;"
      "  lodsb              ;"
      "  stosb              ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      "2:                   ;"
      :: "S" (from), "D" (to), "b" (n), "c" (0xFFFFFFFF) );

  return to;
};


tchar *cschr( const tchar *cs, tchar c )
{
  tchar *res;

  ASM("cld                  ;"
      "1:                   ;"
      "  lodsb              ;"
      "  cmp %%al, %%bl     ;"
      "  je 3f              ;"
      "  test %%al, %%al    ;"
      "  jz 2f              ;"
      "  jmp 1b             ;"
      "2:                   ;"
      "  xor %%esi, %%esi   ;"
      "3:                   ;"
      : "=S" (res)
      : "S" (cs), "b" (c) );

  return res;
};


tchar *csrchr( const tchar *cs, tchar c )
{
  tchar *res;

  ASM("cld                  ;"
      "xor %%edi, %%edi     ;"
      "1:                   ;"
      "  lodsb              ;"
      "  cmp %%al, %%bl     ;"
      "  jne 2f             ;"
      "  mov %%esi, %%edi   ;"
      "  dec %%edi          ;"
      "2:                   ;"
      "  test %%al, %%al    ;"
      "  jnz 1b             ;"
      "3:                   ;"
      : "=D" (res)
      : "S" (cs), "b" (c) );

  return res;
};


tchar *cspbrk( const tchar *cs, const tchar *chrset )
{
  tchar *res;

  ASM("cld                  ;"
      "mov %%edi, %%edx     ;"
      "xor %%al, %%al       ;"
      "repne                ;"
      "scasb                ;"
      "not %%ecx            ;"
      "dec %%ecx            ;"
      "mov %%ecx, %%ebx     ;"
      "1:                   ;"
      "  lodsb              ;"
      "  test %%al, %%al    ;"
      "  je 2f              ;"
      "  mov %%ebx, %%ecx   ;"
      "  mov %%edx, %%edi   ;"
      "  repne              ;"
      "  scasb              ;"
      "  jne 1b             ;"
      "  dec %%esi          ;"
      "  jmp 3f             ;"
      "2:                   ;"
      "  xor %%esi, %%esi   ;"
      "3:                   ;"
      : "=S" (res)
      : "S" (cs), "D" (chrset), "c" (0xFFFFFFFF) );

  return res;
};


tchar *csstr( const tchar *cs, const tchar *subcs )
{
  tchar *res;

  ASM("cld                  ;"
      "mov %%edi, %%edx     ;"
      "xor %%al, %%al       ;"
      "repne                ;"
      "scasb                ;"
      "not %%ecx            ;"
      "dec %%ecx            ;"
      "mov %%ecx, %%ebx     ;"
      "1:                   ;"
      "  mov %%esi, %%eax   ;"
      "  mov %%edx, %%edi   ;"
      "  mov %%ebx, %%ecx   ;"
      "  repe               ;"
      "  cmpsb              ;"
      "  je 2f              ;"
      "  xchg %%eax, %%esi  ;"
      "  inc %%esi          ;"
      "  cmpb $0, -1(%%eax) ;"
      "  jne 1b             ;"
      "  xor %%eax, %%eax   ;"
      "2:                   ;"
      : "=a" (res)
      : "S" (cs), "D" (subcs), "c" (0xFFFFFFFF) );

  return res;
};

tchar *utocshex( u32 value )
{
  static const tchar digits[] = "0123456789ABCDEF";
  static tchar res[] = "00000000";

  res[7] = digits[value & 0xF];
  res[6] = digits[(value >>  4) & 0xF];
  res[5] = digits[(value >>  8) & 0xF];
  res[4] = digits[(value >> 12) & 0xF];
  res[3] = digits[(value >> 16) & 0xF];
  res[2] = digits[(value >> 20) & 0xF];
  res[1] = digits[(value >> 24) & 0xF];
  res[0] = digits[(value >> 28) & 0xF];

  return res;
};
