/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_CLOCK_C
#define FENIX_CLOCK_C

#include "../include/aliases.h"
#include "../include/utility.h"
#include "../include/console.h"
#include "../include/cmos.h"
#include "../include/clock.h"

const tchar *weekDayNames[] = { "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat" };
DateTime startupDateTime;


void readSystemClock( DateTime *datetime )
{
  datetime->year    = BCDToBin8(rdcmos(CMOS_CENTURY)) * 100 + rdcmos( CMOS_YEAR );    // 0x32 - Век в BCD формате

  datetime->month   = rdcmos( CMOS_MONTH );
  datetime->day     = rdcmos( CMOS_DAY );

  datetime->weekDay = rdcmos( CMOS_WEEKDAY );

  datetime->hour    = rdcmos( CMOS_HOUR );
  datetime->minute  = rdcmos( CMOS_MINUTE );
  datetime->second  = rdcmos( CMOS_SECOND );
};

#endif
