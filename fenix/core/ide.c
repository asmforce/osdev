/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_IDE_C
#define FENIX_IDE_C

#include "../include/aliases.h"
#include "../include/io.h"
#include "../include/ide.h"


#define ReadReg( channel, register )          rdio8( channel + register )
#define WriteReg( channel, register, value )  wrio8( value, channel + register )

#define ChannelCli( channel )      WriteReg( channel, IdeRegControl, 0x02 )
#define ChannelSti( channel )      WriteReg( channel, IdeRegControl, 0x00 )
#define ResetController( channel ) WriteReg( channel, IdeRegControl, 0x0F )

//#define CHANNELS_NUMBER 4
//bool channelFree[CHANNELS_NUMBER];






static inline bool waitWhileBusy( IdeChannel channel )
{
  u16 retries = 10000;
  while( ReadReg(channel,IdeRegStatus) & IdeStatusBusy && --retries );
  return retries;
};

static inline bool waitUntilReady( IdeChannel channel )
{
  u16 retries = 10000;
  while( !(ReadReg(channel,IdeRegStatus) & IdeStatusReady) && --retries );
  return retries;
};

static inline bool waitUntilDrq( IdeChannel channel )
{
  u16 retries = 10000;
  while( !(ReadReg(channel,IdeRegStatus) & IdeStatusDrq) && --retries );
  return retries;
};








IdeError ideReadSector( void *buffer, IdeChannel channel, IdeDrive drive, u32 sector )
{
  ChannelCli( channel );

  if( !waitWhileBusy(channel) )  return IdeErrorTimeOut;

  WriteReg( channel, IdeRegNSec, 1 );
  WriteReg( channel, IdeReg0Sec, sector & 0x000000FF );
  WriteReg( channel, IdeReg1Sec, (sector & 0x0000FF00) >> 8 );
  WriteReg( channel, IdeReg2Sec, (sector & 0x00FF0000) >> 16 );
  WriteReg( channel, IdeReg3Sec, 0xE0 | ((sector & 0x0F000000)>>24) | ((drive & 0x1)<<4) );

  if( !waitWhileBusy(channel) )  return IdeErrorTimeOut;
  if( !waitUntilReady(channel) )  return IdeErrorTimeOut;

  WriteReg( channel, IdeRegCommand, IdeCmdRead );

  if( !waitWhileBusy(channel) )  return IdeErrorTimeOut;
  if( !waitUntilDrq(channel) )  return IdeErrorTimeOut;
  if( (ReadReg(channel,IdeRegStatus) & IdeStatusError) )
  {
    u8 error = ReadReg( channel, IdeRegError );
    ResetController( channel );
    return error;
  };

  ASM("cld ; rep ; insw" :: "d" (channel + IdeRegData), "c" (0x100), "D" (buffer) );

  ChannelSti( channel );
  return 0;
};

IdeError ideWriteSector( const void *buffer, IdeChannel channel, IdeDrive drive, u32 sector )
{
  ChannelCli( channel );

  if( !waitWhileBusy(channel) )  return IdeErrorTimeOut;

  WriteReg( channel, IdeRegNSec, 1 );
  WriteReg( channel, IdeReg0Sec, sector & 0x000000FF );
  WriteReg( channel, IdeReg1Sec, (sector & 0x0000FF00) >> 8 );
  WriteReg( channel, IdeReg2Sec, (sector & 0x00FF0000) >> 16 );
  WriteReg( channel, IdeReg3Sec, 0xE0 | ((sector & 0x0F000000)>>24) | ((drive & 0x1)<<4) );

  if( !waitWhileBusy(channel) )  return IdeErrorTimeOut;
  if( !waitUntilReady(channel) )  return IdeErrorTimeOut;

  WriteReg( channel, IdeRegCommand, IdeCmdWrite );

  if( !waitWhileBusy(channel) )  return IdeErrorTimeOut;
  if( !waitUntilDrq(channel) )  return IdeErrorTimeOut;
  if( (ReadReg(channel,IdeRegStatus) & IdeStatusError) )
  {
    u8 error = ReadReg( channel, IdeRegError );
    ResetController( channel );
    return error;
  };

  ASM("cld ; rep ; outsw" :: "d" (channel + IdeRegData), "c" (0x100), "S" (buffer) );

  ChannelSti( channel );
  return 0;
};

#endif
