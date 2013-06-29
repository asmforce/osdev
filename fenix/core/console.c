/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_CONSOLE_C
#define FENIX_CONSOLE_C

#include "../include/aliases.h"
#include "../include/string.h"
#include "../include/console.h"
#include "../include/io.h"

#define VGA_MOR_PORT 0x3CC

static u16 videoIoPort;
static u32 videoMemory;
static ScreenCharacter *videomem;


static inline void ramset( void *to, u32 c, u32 n )
{
  ASM("cld\n\t"
      "movl %%ecx, %%ebx\n\t"
      "shrl $2, %%ecx\n\t"
      "rep stosl\n\t"
      "movl %%ebx, %%ecx\n\t"
      "andl $3, %%ecx\n\t"
      "rep stosb"
      ::"D" (to), "a" (c), "c" (n) );
};






void configureConsole( u8 color )
{
  if( rdio8(VGA_MOR_PORT) & 0x01 )
  {
    videoIoPort = 0x3D4;
    videoMemory = 0xB8000;
  } else {
    videoIoPort = 0x3B4;
    videoMemory = 0xB0000;
  };
  clearScreen( color );
};

void clearScreen( u8 color )
{
  videomem = (ScreenCharacter *) videoMemory;
  ramset( videomem, 0x00200020 | (u32)color << 24 | (u32)color << 8, SCREEN_TEXT_HEIGHT * SCREEN_TEXT_WIDTH << 1 );
};


void clearLine( u8 color )
{
  videomem -= (((u32) videomem - videoMemory) >> 1) % SCREEN_TEXT_WIDTH;
  ramset( videomem, 0x00200020 | (u32)color << 24 | (u32)color << 8, SCREEN_TEXT_WIDTH << 1 );
};


void printc( tchar c )
{
  switch( c )
  {
    case '\n':
      videomem += SCREEN_TEXT_WIDTH;
    case '\r':
      videomem -= (((u32) videomem - videoMemory) >> 1) % SCREEN_TEXT_WIDTH;
      return;

    case '\t':
      videomem += 3;
      return;

    case '\b':
      --videomem;
      videomem->character = ' ';
      return;

    default:
      videomem->character = c;
      ++videomem;
      return;
  };
};

void prints( const tchar *cs )
{
  while( *cs )
  {
    printc( *cs );
    ++cs;
  };
};

// $s - string -> as string
// $c - char -> as character
// $i - i32 -> as i32
// $u - u32 -> as u32
void printf( const tchar *s, ... )
{
  u32 args = (u32) &s + sizeof( tchar* );

  while( *s )
  {
    switch( *s )
    {
    case '$':
      ++s;
      switch( *s )
      {
      case 's':  prints( *((const tchar**) args) );
        break;

      case 'c':  printc( *((tchar*) args) );
        break;

      case 'i':  prints( i32ToString(*((i32*) args),10) );
        break;

      case 'u':  prints( u32ToString(*((u32*) args),10) );
        break;

      default:
        printc( '$' );
        printc( *s );
      };
      ++s;
      args += 4;
      continue;

    default:
      printc( *s );
    };

    ++s;
  };
};


#endif
