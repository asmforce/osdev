/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_CLOCK_H
#define FENIX_CLOCK_H

#include "aliases.h"
#include "cmos.h"
#include "console.h"

typedef struct
{
  u16 year;
  u8  month;
  u8  day;
  u8  weekDay;

  u8  hour;
  u8  minute;
  u8  second;
}  DateTime;

extern const tchar    *weekDayNames[];
extern DateTime startupDateTime;


static inline void configureClock()
{
  //  Устанавливаем формат 24 часа
  //  Устанавливаем формат bin вместо bcd (по-умолчанию выбран bcd)
  wrcmos( rdcmos(CMOS_RTC_STATUSB) | 0x4 | 0x2, CMOS_RTC_STATUSB );

  //  Если батарея разряжена, - выдаем сообщение
  if( !(rdcmos(CMOS_RTC_STATUSD) & 0x80) )  prints("warning: cmos battery is low\n");
};

void readSystemClock( DateTime *datetime );

#endif
