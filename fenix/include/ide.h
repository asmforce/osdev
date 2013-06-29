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
  IdeRegData    = 0x000,          // Регистр данных. Единственный 16-тибитный регистра
  IdeRegError   = 0x001,          // Регистр ошибок. Хранит код ошибки, если младший бит регистра IdeRegStatus - единица
  IdeRegNSec    = 0x002,          // Счетчик секторов. Используется при обработке множества секторов за раз
  IdeReg0Sec    = 0x003,          // Биты [0:7] LFB адреса
  IdeReg1Sec    = 0x004,          // Биты [8:15] LFB адреса
  IdeReg2Sec    = 0x005,          // Биты [16:23] LFB адреса
  IdeReg3Sec    = 0x006,          // Биты [24:27] LFB адреса, режим адресации CHS/LFB, устройство Master/Slave
  IdeRegStatus  = 0x007,          // Регистр статуса. Описывает состояние устройства
  IdeRegCommand = IdeRegStatus,   // Регистр команды (запись)
  IdeRegProps   = IdeRegError,    // Регистр свойств (запись)
  IdeRegControl = 0x206           // Регистр дополнительного управления. Используются биты 1(прерывания от устройства 1-Запрещены, 0-Разрешены) и 2(при установке в 1 - програмный сброс всех (двух) устройств данного канала).
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
  IdeErrorAmnf     = 0x01,        // Не найден адресный маркер сектора
  IdeErrorTconf    = 0x02,        // Не найдена нулевая дорожка при выполнении команды рекалибровки
  IdeErrorAbrt     = 0x04,        // Аварийное прекращение выполнения команды
  IdeErrorMcr      = 0x08,        // Получен запрос на смену носителя
  IdeErrorIdnf     = 0x10,        // Сектор с данными координатами не найден
  IdeErrorMc       = 0x20,        // Произведена смена носителя
  IdeErrorUnc      = 0x40,        // Некорректируемая ошибка данных
//IdeError____     = 0x80,        // Зарезервировано, в данный момент не используется
  IdeErrorTimeOut  = 0xFF         // Вышло время ожидания устройства, пользовательский код ошибки :-)
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

// Функции возвращают 0 в случае успеха или код ошибки
// Если превышен интервал ожидания waitWhileBusy, waitUntilReady, waitUntilDrq возвращаемое значение - 0xFF
IdeError ideIdentify( void *buffer, IdeChannel channel, IdeDrive drive );
IdeError ideReadSector( void *buffer, IdeChannel channel, IdeDrive drive, u32 sector );
IdeError ideWriteSector( const void *buffer, IdeChannel channel, IdeDrive drive, u32 sector );

#endif
