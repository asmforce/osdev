/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#include "../include/aliases.h"

#define PARTITION_INACTIVE 0x00
#define PARTITION_ACTIVE   0x80

typedef struct
{
  u8  active;
  u8  begin[3];
  u8  id;
  u8  end[3];
  u32 beginSector;
  u32 endSector;
} partition;