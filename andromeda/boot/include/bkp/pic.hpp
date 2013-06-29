/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef ANDROMEDA_PIC_HPP
#define ANDROMEDA_PIC_HPP

#include "aliases.hpp"

namespace pic
{
  // read mask (IMR)
  static u16 getmask()
  {
    u16 value;
    GVASM(
      "movw $0xA1, %%dx    ;"
      "inb %%dx, %%al      ;"
      "mov %%al, %%ah      ;"
      "movw $0x21, %%dx    ;"
      "inb %%dx, %%al      ;"
      : "=a" (value)
    );
  };

  // write mask (IMR)
  static void setmask( u16 bits )
  {
    GVASM(
      "movw $0x21, %%dx    ;"
      "outb %%al, %%dx     ;"
      "movw $0xA1, %%dx    ;"
      "mov %%ah, %%al      ;"
      "outb %%al, %%dx     ;"
      :: "a" (bits)
    );
  };

  // change mask (IMR OR BITS)
  static void mask( u16 bits )  {
    GVASM(
      "movw $0x21, %%dx    ;"
      "inb %%dx, %%al      ;"
      "orb %%bl, %%al      ;"
      "nop                 ;"
      "outb %%al, %%dx     ;"
      "movw $0xA1, %%dx    ;"
      "inb %%dx, %%al      ;"
      "orb %%bh, %%al      ;"
      "nop                 ;"
      "outb %%al, %%dx     ;"
      :: "b" (bits)
    );
  };

  // change mask (IMR AND ~BITS)
  static void unmask( u16 bits )  {
    GVASM(
      "notw %%bx           ;"
      "movw $0x21, %%dx    ;"
      "inb %%dx, %%al      ;"
      "andb %%bl, %%al     ;"
      "nop                 ;"
      "outb %%al, %%dx     ;"
      "movw $0xA1, %%dx    ;"
      "inb %%dx, %%al      ;"
      "andb %%bh, %%al     ;"
      "nop                 ;"
      "outb %%al, %%dx     ;"
      :: "b" (bits)
    );
  };

  // send EOI to master/slave pic
  static void eoi( bool masterpic )  {
    GVASM(
      "movb $0x20, %%al     ;"
      "outb %%al, %%dx      ;"
      ::
      "d" (masterpic ? 0x20 : 0xA0)
    );
  };
}; // namespace pic

#endif // ANDROMEDA_PIC_HPP
