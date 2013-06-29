/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_CMOS_H
#define XWORKSPACE_CMOS_H

#include "config.h"

#define CMOS_INDEX_PORT 0x70
#define CMOS_DATA_PORT  0x71


// RTC
#define CMOS_SIGNAL_SECOND  0x01
#define CMOS_SIGNAL_MINUTE  0x03
#define CMOS_SIGNAL_HOUR    0x05

#define CMOS_SECOND         0x00
#define CMOS_MINUTE         0x02
#define CMOS_HOUR           0x04

#define CMOS_WEEKDAY        0x06
#define CMOS_DAY            0x07
#define CMOS_MONTH          0x08
#define CMOS_YEAR           0x09

// Century always - bcd
#define CMOS_CENTURY        0x32

#define CMOS_RTC_STATUSA    0x0A
#define CMOS_RTC_STATUSB    0x0B
#define CMOS_RTC_STATUSC    0x0C
#define CMOS_RTC_STATUSD    0x0D

#define CMOS_POST           0x0E
#define CMOS_RESTART_STATUS 0x0F

#define CMOS_FDC_TYPE       0x10
#define CMOS_HDD_TYPE       0x12
#define CMOS_DEVICES        0x14

#define CMOS_BASE_MEMORYL   0x15
#define CMOS_BASE_MEMORYH   0x16

#define CMOS_HIGH_MEMORYL   0x17
#define CMOS_HIGH_MEMORYH   0x18

#define CMOS_HDD_TYPEC      0x19
#define CMOS_HDD_TYPED      0x1A

#define CMOS_CRCL           0x2F
#define CMOS_CRCH           0x2E

#define CMOS_ATPS           0x33

extern u8 rdcmos( u8 cell );
extern void wrcmos( u8 value, u8 cell );

#endif
