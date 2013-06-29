/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include <aliases.hpp>
#include <pic.hpp>

// read mask (IMR)
u16 pic::getmask()
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
void pic::setmask( u16 bits )
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
void pic::mask( u16 bits )  {
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
void pic::unmask( u16 bits )  {
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
void pic::eoi( bool masterpic )  {
  GVASM(
    "movb $0x20, %%al     ;"
    "outb %%al, %%dx      ;"
    ::
    "d" (masterpic ? 0x20 : 0xA0)
  );
};
