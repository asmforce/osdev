/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_SYSTABLES_H
#define XWORKSPACE_SYSTABLES_H

#include "config.h"

typedef struct
{
  union
  {
    struct { u32 a32,            b32;            };
    struct { u16 a16,    b16,    c16,    d16;    };
    struct { u8  a8, b8, c8, d8, e8, f8, g8, h8; };
  };
} IdtDesc, GdtDesc, LdtDesc, TssDesc;

extern u32 exIdt;
extern u32 exGdt;

#endif
