/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_CMOS_C
#define FENIX_CMOS_C

#include "../include/aliases.h"
#include "../include/asm.h"
#include "../include/io.h"
#include "../include/cmos.h"

u8 rdcmos( u8 cell )
{
  wrio8( cell, CMOS_INDEX_PORT );
  return rdio8( CMOS_DATA_PORT );
};

void wrcmos( u8 value, u8 cell )
{
  wrio8( cell, CMOS_INDEX_PORT );
  wrio8( value, CMOS_DATA_PORT );
};

#endif
