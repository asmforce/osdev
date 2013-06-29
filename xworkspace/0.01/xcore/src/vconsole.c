/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include "config.h"
#include "io.h"
#include "ram.h"

#define VGA_MOR_PORT 0x3CC

typedef struct
{
  tchar code;
  u8    color;
} vchar;

typedef struct
{
  union
  {
    u32    frameBuffer;
    vchar *vchars;
  };
  u16 vgaIoPort;

  u16 area;
  u16 width, height;
  u16 offset;
  tchar caret;
} VConsole;

static VConsole vc0;


void inizVConsole()
{
  if( rdio8(VGA_MOR_PORT) & 0x01 )
  {
    vc0.frameBuffer = 0xB8000;
    vc0.vgaIoPort = 0x3D4;
  } else {
    vc0.frameBuffer = 0xB0000;
    vc0.vgaIoPort = 0x3B4;
  };

  vc0.width = 80;
  vc0.height = 50;
  vc0.area = vc0.width * vc0.height;
  vc0.offset = 0;
  vc0.caret = 0xDB;
};


static void incCaret()
{
  if( ++vc0.offset == vc0.area )
    ramcpy( vc0.vchars, vc0.vchars + vc0.width, vc0.area << 1 );
};


void vcprint( tchar c )
{
  switch( c )
  {
  case '\0':
    return;

  case '\n':
    vc0.vchars[vc0.offset].code = ' ';
    vc0.offset -= vc0.offset % vc0.width;
    vc0.offset += vc0.width;
    if( vc0.offset >= vc0.area )
    {
      vc0.offset -= vc0.width;
      ramcpy( vc0.vchars, vc0.vchars + vc0.width, vc0.area << 1 );
    };
    break;

  case '\t':
    vc0.vchars[vc0.offset].code = ' ';
    incCaret();
    vc0.vchars[vc0.offset].code = ' ';
    incCaret();
    vc0.vchars[vc0.offset].code = ' ';
    incCaret();
    break;

  case '\r':
    vc0.vchars[vc0.offset].code = ' ';
    vc0.offset -= vc0.offset % vc0.width;
    break;

  case '\b':
    vc0.vchars[vc0.offset].code = ' ';
    if( vc0.offset % vc0.width )  --vc0.offset;
    break;

  default:
    vc0.vchars[vc0.offset].code = c;
    incCaret();
  };
  vc0.vchars[vc0.offset].code = vc0.caret;
};


void vsprint( const tchar *cs )
{
  while( *cs )
    vcprint( *(cs++) );
};

/**
void vsprint( tchar *cs )
{
  u32 offset = vc0.frameBuffer + (vc0.offset << 1);

  ASM("mov $0xB9F40, %%ecx   ;"
      "sub %%edi, %%ecx      ;"
      "shr $1, %%ecx         ;"
      "mov $0x0F00, %%eax    ;"
      "1:                    ;"
      "  dec %%ecx           ;"
      "  js 3f               ;"
      "  lodsb               ;"
      "  test %%al, %%al     ;"
      "  jz 3f               ;"
      "  cmp $'\n', %%al     ;"
      "  je control_n        ;"
      "  cmp $'\t', %%al     ;"
      "  je control_t        ;"
      "  cmp $'\r', %%al     ;"
      "  je control_r        ;"
      "  cmp $'\b', %%al     ;"
      "  je control_b        ;"
      "2:                    ;"
      "  stosw               ;"
      "  jmp 1b              ;"
      "control_t:            ;"
      "  mov $'T', %%al      ;"
      "  jmp 2b              ;"
      "control_n:            ;"
      "  add %%edx, %%edi    ;"
      "control_r:            ;"
      "  mov %%eax, %%ebx    ;"
      "  mov %%edi, %%eax    ;"
      "  sub $0xB8000, %%eax ;"
      "  div %%dl            ;"
      "  mov %%ah, %%al      ;"
      "  and $0xFF, %%eax    ;"
      "  sub %%eax, %%edi    ;"
      "  mov %%ebx, %%eax    ;"
      "  jmp 1b              ;"
      "control_b:            ;"
      "  cmp $0xB8000, %%edi ;"
      "  je 1b               ;"
      "  mov $0xB8000, %%eax ;"
      "  jmp 2b              ;"
      "3:                    ;"
      : "=D" (offset)
      : "D" (offset), "d" (vc0.width<<1), "S" (cs) );

  offset -= vc0.frameBuffer;
  offset >>= 1;
  vc0.offset = offset;
};
**/
