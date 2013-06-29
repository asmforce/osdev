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
  u16 getmask();

  // write mask (IMR)
  void setmask( u16 bits );

  // change mask (IMR OR BITS)
  void mask( u16 bits );

  // change mask (IMR AND ~BITS)
  void unmask( u16 bits );

  // send EOI to master/slave pic
  void eoi( bool masterpic );
}; // namespace pic

#endif // ANDROMEDA_PIC_HPP
