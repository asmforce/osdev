/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_IDE_H
#define FENIX_IDE_H

#include "aliases.h"

typedef enum
{
  IdeChannel0 = 0x1F0,
  IdeChannel1 = 0x170,
  IdeChannel2 = 0x1E8,
  IdeChannel3 = 0x168
}  IdeChannel;

typedef enum
{
  IdeMaster = 0,
  IdeSlave  = 1
}  IdeDrive;

typedef enum
{
  IdeRegData    = 0x000,          // ������� ������. ������������ 16-�������� ��������
  IdeRegError   = 0x001,          // ������� ������. ������ ��� ������, ���� ������� ��� �������� IdeRegStatus - �������
  IdeRegNSec    = 0x002,          // ������� ��������. ������������ ��� ��������� ��������� �������� �� ���
  IdeReg0Sec    = 0x003,          // ���� [0:7] LFB ������
  IdeReg1Sec    = 0x004,          // ���� [8:15] LFB ������
  IdeReg2Sec    = 0x005,          // ���� [16:23] LFB ������
  IdeReg3Sec    = 0x006,          // ���� [24:27] LFB ������, ����� ��������� CHS/LFB, ���������� Master/Slave
  IdeRegStatus  = 0x007,          // ������� �������. ��������� ��������� ����������
  IdeRegCommand = IdeRegStatus,   // ������� ������� (������)
  IdeRegProps   = IdeRegError,    // ������� ������� (������)
  IdeRegControl = 0x206           // ������� ��������������� ����������. ������������ ���� 1(���������� �� ���������� 1-���������, 0-���������) � 2(��� ��������� � 1 - ���������� ����� ���� (����) ��������� ������� ������).
}  IdeRegister;

typedef enum
{
  IdeStatusError     = 0x01,
  IdeStatusIndex     = 0x02,
  IdeStatusCorrected = 0x04,
  IdeStatusDrq       = 0x08,
  IdeStatusSeek      = 0x10,
  IdeStatusWrerr     = 0x20,
  IdeStatusReady     = 0x40,
  IdeStatusBusy      = 0x80
}  IdeStatus;

typedef enum
{
  IdeErrorAmnf     = 0x01,        // �� ������ �������� ������ �������
  IdeErrorTconf    = 0x02,        // �� ������� ������� ������� ��� ���������� ������� ������������
  IdeErrorAbrt     = 0x04,        // ��������� ����������� ���������� �������
  IdeErrorMcr      = 0x08,        // ������� ������ �� ����� ��������
  IdeErrorIdnf     = 0x10,        // ������ � ������� ������������ �� ������
  IdeErrorMc       = 0x20,        // ����������� ����� ��������
  IdeErrorUnc      = 0x40,        // ���������������� ������ ������
//IdeError____     = 0x80,        // ���������������, � ������ ������ �� ������������
  IdeErrorTimeOut  = 0xFF         // ����� ����� �������� ����������, ���������������� ��� ������ :-)
}  IdeError;

typedef enum
{
  IdeCmdRestore  = 0x10,
  IdeCmdRead     = 0x20,
  IdeCmdWrite    = 0x30,
  IdeCmdVerify   = 0x40,
  IdeCmdFormat   = 0x50,
  IdeCmdInit     = 0x60,
  IdeCmdSeek     = 0x70,
  IdeCmdDiagnose = 0x90,
  IdeCmdSpecify  = 0x91,
  IdeCmdIdentify = 0xEC,
}  IdeCommand;

// ������� ���������� 0 � ������ ������ ��� ��� ������
// ���� �������� �������� �������� waitWhileBusy, waitUntilReady, waitUntilDrq ������������ �������� - 0xFF
IdeError ideIdentify( void *buffer, IdeChannel channel, IdeDrive drive );
IdeError ideReadSector( void *buffer, IdeChannel channel, IdeDrive drive, u32 sector );
IdeError ideWriteSector( const void *buffer, IdeChannel channel, IdeDrive drive, u32 sector );

#endif
