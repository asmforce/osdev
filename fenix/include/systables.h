/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_SYSTABLES_H
#define FENIX_SYSTABLES_H

#include "aliases.h"

typedef struct
{
  union
  {
    struct { u32 a32,            b32;            };
    struct { u16 a16,    b16,    c16,    d16;    };
    struct { u8  a8, b8, c8, d8, e8, f8, g8, h8; };
  };
} IdtDesc, GdtDesc, LdtDesc, TssDesc;


typedef struct
{
  u16       size;
  IdtDesc  *table;
} IdtReg, GdtReg;


extern IdtDesc *idtable;
extern GdtDesc *gdtable;

void configureGates();

#endif
