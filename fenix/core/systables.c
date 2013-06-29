/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_SYSTABLES_C
#define FENIX_SYSTABLES_C

#include "../include/aliases.h"
#include "../include/systables.h"

IdtDesc *idtable;
GdtDesc *gdtable;

void configureGates()
{
  idtable = (IdtDesc*) 0x500;
  gdtable = (GdtDesc*) 0xD00;
};

#endif
