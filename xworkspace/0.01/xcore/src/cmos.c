/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include "config.h"
#include "io.h"
#include "cmos.h"

u8 rdcmos( u8 cell )
{
  WRIO8( cell, CMOS_INDEX_PORT );
  RDIO8( cell, CMOS_DATA_PORT );
  return cell;
};

void wrcmos( u8 value, u8 cell )
{
  WRIO8( cell, CMOS_INDEX_PORT );
  WRIO8( value, CMOS_DATA_PORT );
};
