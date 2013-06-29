/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_EXCEPTION_H
#define FENIX_EXCEPTION_H

#include "aliases.h"

extern void onDivideError();
extern void onDebug();
extern void onNmi();
extern void onBreakpoint();
extern void onOverflow();
extern void onBoundsExceeded();
extern void onInvalidOpcode();
extern void onNoX87();
extern void onDoubleFault();
extern void onX87Overrun();
extern void onInvalidTss();
extern void onSegmentNotPresent();
extern void onStackSegmentFault();
extern void onGeneralProtection();
extern void onPageFault();
extern void onReserved();
extern void onX87Fault();
extern void onAlignmentCheck();

#endif
