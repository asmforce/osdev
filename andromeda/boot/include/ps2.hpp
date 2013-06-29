/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef ANDROMEDA_PS2_HPP
#define ANDROMEDA_PS2_HPP

#include <aliases.hpp>
#include <systables.hpp>
#include <pic.hpp>
#include <io.hpp>


#define MOUSE_IRQ     12
#define MOUSE_IRQMASK 0x0800

#define	MOUSEPORT_DATA      0x23C
#define	MOUSEPORT_SIGNATURE 0x23D
#define	MOUSEPORT_CONTROL   0x23E
#define MOUSEPORT_INTERRUPT 0x23E
#define	MOUSEPORT_CONFIG    0x23F

// disable mouse interrupts
#define MOUSE_CLI io::o8( MOUSEPORT(CONTROL), 0x10 )
// enable mouse interrupts
#define MOUSE_STI io::o8( MOUSEPORT(CONTROL), 0x00 )

#define	MOUSE_IDX_XL 0x80
#define	MOUSE_IDX_XH 0xA0
#define	MOUSE_IDX_YL 0xC0
#define	MOUSE_IDX_YH 0xE0

#define MOUSE_CONFIG_BYTE    0x91
#define MOUSE_DEFAULT_MODE   0x90
#define MOUSE_SIGNATURE_BYTE 0xA5

#define MOUSE(x)     (MOUSE_     ## x)
#define MOUSEPORT(x) (MOUSEPORT_ ## x)


namespace ps2
{
  namespace mouse
  {
    bool presence;
    bool active;

    // initialize ps/2 mouse
    static void setup( u32 attempts = 100000 )
    {
      // unmask irq12
      pic::unmask( MOUSE(IRQMASK) );

      // configure mouse
      io::o8( MOUSEPORT(CONFIG), MOUSE(CONFIG_BYTE) );
      io::o8( MOUSEPORT(SIGNATURE), MOUSE(SIGNATURE_BYTE) );

      active = false;
      while( attempts-- )
        if( io::i8(MOUSEPORT(SIGNATURE)) != MOUSE(SIGNATURE_BYTE) )  {
          presence = false;
          return;
        }

      // turn to default mode
      io::o8( MOUSEPORT(CONFIG), MOUSE(CONFIG_BYTE) );
      // make inactive
      //MOUSE(CLI);
      presence = true;
    }
  }

  namespace keyboard
  {
  }
}

#endif // ANDROMEDA_PS2_HPP
