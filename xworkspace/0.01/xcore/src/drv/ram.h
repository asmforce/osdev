/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_DRV_RAM_H
#define XWORKSPACE_DRV_RAM_H

#include "config.h"

static u32 allocPointer = 1024;

static void *allocate( u32 size )
{
  void *res = (void*) allocPointer;
  allocPointer += size;
  return res;
};

// Currently is dummy
static void deallocate( void *p )
{
};

#endif
