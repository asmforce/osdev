/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_MEMORY_C
#define FENIX_MEMORY_C

#include "../include/aliases.h"

u32 memoryTotal;

void configureRam()
{
  u8  *value = 0;

  for( memoryTotal = 0x100000; memoryTotal != 0xFFFFFFFF; memoryTotal += 0x100000 )
  {
    value[memoryTotal] = 0xAA;
    if( value[memoryTotal] != 0xAA )
      return;
  };
};

#endif
