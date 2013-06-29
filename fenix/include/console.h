/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_CONSOLE_H
#define FENIX_CONSOLE_H

#include "aliases.h"

#define SCREEN_TEXT_HEIGHT 50
#define SCREEN_TEXT_WIDTH  80

typedef struct
{
  u8 character;
  u8 color;
} ScreenCharacter;

void configureConsole( u8 color );
void clearScreen( u8 color );
void clearLine( u8 color );

void printc( tchar c );
void prints( const tchar *cs );
void printf( const tchar *s, ... );

#endif
