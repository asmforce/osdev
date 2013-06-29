/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_STRING_C
#define FENIX_STRING_C

#include "../include/aliases.h"
#include "../include/string.h"

static tchar __buffer[33] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, '\0' };

const tchar *u32ToString( u32 num, u8 radix )
{
  tchar *cs = __buffer + 31;
  u16 rem;
  do
  {
    rem = num % radix;
    if( rem < 10 )
    {
      *cs = rem + '0';
    } else {
      *cs = rem + 'A' - 10;
    };
    --cs;
  } while( num /= radix );
  return ++cs;
};

const tchar *i32ToString( i32 num, u8 radix )
{
  bool negative = 0;
  if( num < 0 )
  {
    negative = 1;
    num = -num;
  };


  tchar *cs = __buffer + 31;
  u16 rem;
  do
  {
    rem = num % radix;
    if( rem < 10 )
    {
      *cs = rem + '0';
    } else {
      *cs = rem + 'A' - 10;
    };
    --cs;
  } while( num /= radix );

  if( negative )
  {
    *cs = '-';
    return cs;
  };
  return ++cs;
};

#endif
