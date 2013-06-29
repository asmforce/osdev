/*
* os fenix
* asmforce (nickname) asmforce@ukr.net
* 2010
*/

#pragma pack(1)
//asm(".intel_syntax noprefix\n");
//gcc -masm-intel

#include "include/aliases.h"

#include "include/asm.h"
#include "include/io.h"
#include "include/mutex.h"

#include "include/systables.h"
#include "include/exception.h"
#include "include/gates.h"
#include "include/task.h"

#include "include/string.h"
#include "include/memory.h"

#include "include/timers.h"
#include "include/cmos.h"
#include "include/clock.h"

#include "include/console.h"
#include "include/ide.h"



void dump( u32 base, u32 n )
{
  u8 *p = (u8*) base;
  u32 i;

  for( i = 0; i != n; ++i )
    printf( "$u ", p[i] );

  printc( '\n' );
};








tchar *keyNames[] = { "",          "ESC",       "1",         "2",         "3",         "4",         "5",         "6",         "7",         "8",
                      "9",         "0",         "-",         "=",         "Backspace", "Tab",       "q",         "w",         "e",         "r",
                      "t",         "y",         "u",         "i",         "o",         "p",         "[",         "]",         "Enter",     "Ctrl",
                      "a",         "s",         "d",         "f",         "g",         "h",         "j",         "k",         "l",         ";",
                      "\'",        "`",         "LShift",    "\\",        "z",         "x",         "c",         "v",         "b",         "n",
                      "m",         ",",         ".",         "/",         "RShift",    "PrtSc",     "Alt",       "Space",     "CapsLk",    "F1",
                      "F2",        "F3",        "F4",        "F5",        "F6",        "F7",        "F8",        "F9",        "F10",       "Pause",
                      "F12",       "71",        "Up",        "73",        "74",        "Left",      "76",        "Right",     "78",        "79",
                      "Down",      "81",        "Insert",    "Delete",    "84",        "85",        "86",        "F11",       "F12",       "89",
                      "90",        "WinKey",    "92",        "WinMenu",   "94",        "95",        "Switch-96", "97",        "98",        "99",
                      "100",       "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE" };

tchar *keyShiftedNames[] = { "",          "ESC",       "!",         "@",         "#",         "$",         "%",         "^",         "&",         "*",
                             "(",         ")",         "_",         "+",         "Backspace", "Tab",       "Q",         "W",         "E",         "R",
                             "T",         "Y",         "U",         "I",         "O",         "P",         "{",         "}",         "Enter",     "Ctrl",
                             "A",         "S",         "D",         "F",         "G",         "H",         "J",         "K",         "L",         ":",
                             "\"",        "~",         "LShift",    "|",         "Z",         "X",         "C",         "V",         "B",         "N",
                             "M",         "<",         ">",         "?",         "RShift",    "PrtSc",     "Alt",       "Space",     "CapsLk",    "F1",
                             "F2",        "F3",        "F4",        "F5",        "F6",        "F7",        "F8",        "F9",        "F10",       "Pause",
                             "F12",       "71",        "Up",        "73",        "74",        "Left",      "76",        "Right",     "78",        "79",
                             "Down",      "81",        "Insert",    "Delete",    "84",        "85",        "86",        "F11",       "F12",       "89",
                             "90",        "WinKey",    "92",        "WinMenu",   "94",        "95",        "Switch-96", "97",        "98",        "99",
                             "100",       "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",
                             "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE",      "MORE" };





extern void onTimer();









extern void onKeyboard();
__asm__("_onKeyboard:       ;"    // IRQ1
        "pusha              ;"
        "xor %eax, %eax     ;"
        "inb $0x60, %al     ;"
        "push %eax          ;"
        "call _doOnKeyboard ;"
        "pop %eax           ;"
        "popa               ;"
        "sti                ;"
        "iret               ;");

static u8 shiftState = 0;
void doOnKeyboard( u8 scancode )
{
  //u8 value = rdio8( 0x60 );
  switch( scancode & 0x7F )
  {
  case 1:
    machineReboot();

  case 20:
    printf( "$u.$u.$u $s $u:$u:$u\n", startupDateTime.day, startupDateTime.month, startupDateTime.year, weekDayNames[startupDateTime.weekDay], startupDateTime.hour, startupDateTime.minute, startupDateTime.second );
    return;

  case 83:
    clearScreen( 0x0F );
    return;

  case 42:
  case 54:
    shiftState = !(scancode & 0x80);
    return;

  default:
    if( scancode & 0x80 )  return;
    prints( shiftState ? keyShiftedNames[scancode] : keyNames[scancode] );
  };
};











void setup()
{
  u16 value;
  // Тут мы задаем маску, что позволяет маскировать выборочные IRQ
  wrio8( 0x00, 0x21 ); // 0x21 - ведущий контроллер прерываний
  wrio8( 0x00, 0xA1 ); // 0xA1 - ведомый контроллер прерываний

  // Инициализируем память, производится подсчет доступной RAM
  configureRam();

  // Функция initGates() инициализирует idttable
  configureGates(); 

  // Устанавливаем обработчики исключений
  setTrapGate( &onDivideError, 0x00 );
  setTrapGate( &onDebug, 0x01 );
  setTrapGate( &onNmi, 0x02 );
  setTrapGate( &onBreakpoint, 0x03 );
  setTrapGate( &onOverflow, 0x04 );
  setTrapGate( &onBoundsExceeded, 0x05 );
  setTrapGate( &onInvalidOpcode, 0x06 );
  setTrapGate( &onNoX87, 0x07 );
  setTrapGate( &onDoubleFault, 0x08 );
  setTrapGate( &onX87Overrun, 0x09 );
  setTrapGate( &onInvalidTss, 0x0A );
  setTrapGate( &onSegmentNotPresent, 0x0B );
  setTrapGate( &onStackSegmentFault, 0x0C );
  setTrapGate( &onGeneralProtection, 0x0D );
  setTrapGate( &onPageFault, 0x0E );
  setTrapGate( &onReserved, 0x0F );
  setTrapGate( &onX87Fault, 0x10 );
  setTrapGate( &onAlignmentCheck, 0x11 );

  for( value = 0x12; value != 0x20; ++value )  setTrapGate( &onReserved, value );

  // Устанавливаем обработчики прерываний
  setTrapGate( &onTimer, 0x20 );
  setTrapGate( &onKeyboard, 0x21 );

  // Конфигурируем i8253-совместимый контроллер
  configure8253( I8253_CONFIG_CH0 | I8253_READ_LHB | I8253_MODE3 | I8253_BIN );
  set8253( 0x7FFF, I8253_CH0 );

  // Эта функция инициализирует консоль:
  // устанавливает указатель на видеопамять,
  // очищает экран, указывая для каждого символа
  // палитру - аргумент функции
  configureConsole( 0x0F );

  // Эта функция инициализирует часы реального времени:
  // включает режим bin вместо bcd, и 24х-часовой формат
  configureClock();
/*
  value = rdcmos( CMOS_SECOND );
  while( rdcmos(CMOS_SECOND) == value )  NOP();
*/
  readSystemClock( &startupDateTime );

  // Инициализируем многозадачность
  // Доступен только один контекст - task0
  configureScheduler();

  prints("::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::\n");
};












ScreenCharacter *videomem = (ScreenCharacter*) 0xB8000;

void doTask1()
{
  while( 1 )
  {
    //ASM("xor %bl, %bl; div %bl");
    ++videomem[1].character;
  };
};
MAKE_ASM_TASK_CALL( doTask1, entryTask1 );


void doTask2()
{
  while( 1 )
  {
    //ASM("xor %bl, %bl; div %bl");
    ++videomem[2].character;
  };
};
MAKE_ASM_TASK_CALL( doTask2, entryTask2 );













void osmain()
{
  setup();

  Task task1, task2;
  // 0x9FFFF - Дно стека ядра, т.е. task0
  createTask( &task1, (u32) &entryTask1, 0x9FFFF-1024 );
  createTask( &task2, (u32) &entryTask2, 0x9FFFF-2048 );

  STI();
  while(1)
  {
    ++videomem[0].character;
    HLT();
  };
};
