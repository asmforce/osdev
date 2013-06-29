/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_TIMERS_H
#define FENIX_TIMERS_H

#include "aliases.h"
#include "io.h"

// IO Ports
#define I8253_MODE_PORT 0x43
#define I8253_CH0       0x40
#define I8253_CH1       0x41 // ??? Может применяться для регенерации динамической памяти
#define I8253_CH2       0x42



// Lock channels
#define I8253_LOCK_CH0 0x02
#define I8253_LOCK_CH1 0x04
#define I8253_LOCK_CH2 0x08

// Channel change
#define I8253_CONFIG_CH0 0x00
#define I8253_CONFIG_CH1 0x40
#define I8253_CONFIG_CH2 0x80

// Read\Write mode
#define I8253_READ_LB  0x10
#define I8253_READ_HB  0x20
#define I8253_READ_LHB 0x30

// Timer mode
#define I8253_MODE0  0x00
//#define I8253_MODE1  0x02 // not accessed at PC
#define I8253_MODE2  0x04
#define I8253_MODE3  0x06
#define I8253_MODE4  0x08
//#define I8253_MODE5  0x0A // not accessed at PC

// Data format
#define I8253_BIN  0x00
#define I8253_BCD  0x08



#define configure8253( configuration )  wrio8( (configuration), I8253_MODE_PORT )

//#define lock8253( channels )            wrio8( (channels) | 0xD0, I8253_MODE_PORT )  // ??? Не проверено

#define set8253( counter, channel )    { wrio8( (counter&0xFF), channel ); wrio8( (counter>>8), channel ); }
#define set8253( counter, channel )    { wrio8( (counter&0xFF), channel ); wrio8( (counter>>8), channel ); }
#define set8253( counter, channel )    { wrio8( (counter&0xFF), channel ); wrio8( (counter>>8), channel ); }

#define get8253( channel )             (rdio8( channel ) | rdio8( channel ) << 8)
#define get8253( channel )             (rdio8( channel ) | rdio8( channel ) << 8)
#define get8253( channel )             (rdio8( channel ) | rdio8( channel ) << 8)


#endif
