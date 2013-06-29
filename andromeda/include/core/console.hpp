/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef ANDROMEDA_CONSOLE_HPP
#define ANDROMEDA_CONSOLE_HPP

#include <aliases.hpp>
#include <core/io.hpp>

// Warning: this header should be removed later
// actually it's required for debugging and tracing

namespace console
{
  // internal variables
  // mutable constants :)
  namespace imp  {
    // control io-ports
    static u16 vgaidx;
    static u16 vgadata;
    // video-memory layout
    static u32 video;
    static u32 cpos;
    // imp::columns - symbols per line
    // imp::rows - lines per screen
    static u16 columns, rows;
    static u32 areasize;

//** TODO: revision required
    static void setreg( u8 idx, u8 data );
    // maybe doesn't available
    // static u8 getreg( u8 idx );

    static void setcaret( u16 pos );
//**/
  };  // namespace imp


  // sets up console subsystem
  // includes `cls`
  static void setup();

  static void cls();
  // returns a `new` line's index
  static u16 newline();

  // screen navigation
  static u32 pos();
  static u32 pos( u32 line, u32 column );
  static u32 line();
  static u32 column();

  // printing functions
  // put char
  static void putc( tchar c );

  // put null-terminated char-string
  static void putcs( const tchar *cs );

  // uses `pattern` as format string
  // static void outpattern( tchar *pattern, ... );
}; // namespace console





//** TODO: revision required
void console::imp::setreg( u8 idx, u8 data )  {
  io::o8( vgaidx, idx );
  io::o8( vgadata, data );
};

void console::imp::setcaret( u16 pos )  {
  setreg( 0x0F, pos & 0xFF );
  setreg( 0x0E, pos >> 8 );
};
//**/


void console::setup()
{
  // 0x3CC - vga compatible port
  if( io::i8(0x3CC) & 0x01 )
  {
    // ega, vga, svga (color)
    imp::video = 0xB8000;
    imp::vgaidx = 0x3D4;
    imp::vgadata = 0x3D5;
  } else {
    // mda, cga, ega, vga, svga (mono)
    imp::video = 0xB0000;
    imp::vgaidx = 0x3B4;
    imp::vgadata = 0x3B5;
  };

  // warning: magic numbers
  // 40x80 is vga-compatible text-resolution
  // it is default resolution
  // imp::cpos = 0uL; // cls does it itself
  imp::rows = 25;
  imp::columns = 80;
  imp::areasize = imp::rows * imp::columns;

  // clean screen
  cls();
};


void console::cls()
{
  // current position
  imp::cpos = 0uL;

//** TODO: revision required
  // sets up caret position
  imp::setcaret( imp::cpos );

  // disables caret
  imp::setreg( 0x0A, 0xFF );
  imp::setreg( 0x0B, 0xFF );
//**/

  // empty charplace
  // color -> 0E
  // char  -> 00
  u16 emptycp = 0x0E00;
  GVASM(
    "rep stosw ;"
    :
    :
    "a" (emptycp),
    "D" (imp::video),
    "c" (imp::areasize)
  );
};

u16 console::newline()
{
  // `imp::cpos % imp::columns` - offset in current line
  imp::cpos += imp::columns - imp::cpos % imp::columns;
  // integer division
  return imp::cpos / imp::columns;
};


u32 console::pos()  {
  return imp::cpos;
};

u32 console::pos( u32 line, u32 column )  {
  // imp::columns - symbols per line
  imp::cpos = imp::columns * line + column;
  return imp::cpos;
};

u32 console::line()  {
  // imp::columns - symbols per line
  return imp::cpos / imp::columns;
};

u32 console::column()  {
  // imp::columns - symbols per line
  return imp::cpos % imp::columns;
};


void console::putc( tchar c )
{
  GVASM(
    "movb %%al, (%%edx,%%edi,2) ;"
    "incl %%edi                 ;"
    :
    "=D" (imp::cpos)
    :
    "a" (c),
    "d" (imp::video),
    "D" (imp::cpos)
  );
  // set caret to current position
  // imp::setcaret( imp::cpos );
};


void console::putcs( const tchar *cs )
{
  GVASM(
    "1:                         ;"
    "lodsb                      ;"
    "test %%al, %%al            ;"
    "jz 2f                      ;"
    "movb %%al, (%%edx,%%edi,2) ;"
    "incl %%edi                 ;"
    "jmp 1b                     ;"
    "2:                         ;"
    :
    "=D" (imp::cpos)
    :
    "S" (cs),
    "d" (imp::video),
    "D" (imp::cpos)
  );
  // set caret to current position
  // imp::setcaret( imp::cpos );
};

#endif // ANDROMEDA_CONSOLE_HPP
