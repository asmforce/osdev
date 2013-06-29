/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_UTILITY_H
#define FENIX_UTILITY_H

#include "aliases.h"

// BYTE BCD -> BIN
#define  BCDToBin8( value )           \
(                                     \
  ( ((value) & 0xF0) >> 4  ) * 10 +   \
  (  (value) & 0x0F        )          \
)

// BYTE BIN -> BCD
#define  BinToBCD8( value )                   \
(                                             \
  ((value) % 10) | ((((value)/10) % 10) << 4) \
)

#endif
