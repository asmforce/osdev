/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_PIT_H
#define XWORKSPACE_PIT_H

#include "config.h"
#include "io.h"

#define INIT_PIT( configuration )      wrio8( (configuration), PIT_BASE )
#define SET_PIT( counter, channel )    { wrio8( (counter&0xFF), channel ); wrio8( (counter>>8), channel ); }
#define GET_PIT( channel )             ( rdio8( channel ) | rdio8( channel ) << 8 )

#define PIT_FREQ 1193181
// hz may be >= 19
#define PIT_DIVIDER( hz ) (PIT_FREQ/(hz))

// IO Ports
#define PIT_BASE 0x43
#define PIT_CH0  0x40
#define PIT_CH1  0x41 // ??? Can be use for regeneration of dynamic memory
#define PIT_CH2  0x42

// Lock channels
#define PIT_LOCK_CH0 0x02
#define PIT_LOCK_CH1 0x04
#define PIT_LOCK_CH2 0x08

// Channel change
#define PIT_CONFIG_CH0 0x00
#define PIT_CONFIG_CH1 0x40
#define PIT_CONFIG_CH2 0x80

// Read\Write mode
#define PIT_READ_LB  0x10
#define PIT_READ_HB  0x20
#define PIT_READ_LHB 0x30

// Timer mode
#define PIT_MODE0  0x00
//#define PIT_MODE1  0x02 // not accessed at PC
#define PIT_MODE2  0x04
#define PIT_MODE3  0x06
#define PIT_MODE4  0x08
//#define PIT_MODE5  0x0A // not accessed at PC

// Data format
#define PIT_BIN  0x00
#define PIT_BCD  0x08

#endif
