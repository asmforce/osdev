/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_MUTEX_H
#define FENIX_MUTEX_H

#include "aliases.h"

typedef u8 mutex;

static void inline lock( mutex *m )
{
  ASM("mov $1, %%al       ;"
      "try_lock:          ;"
      "xchg %%al, (%%edi) ;"
      "test %%al, %%al    ;"
      "jz exit            ;"
      "hlt                ;"
      "jmp try_lock       ;"
      "exit:              ;"
      :: "D" (m) );
};

static void inline unlock( mutex *m )
{
  ASM("movb $0, (%%edi)   ;"
      :: "D" (m) );
};

#endif
