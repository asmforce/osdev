/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#include <xworkspace/config.h>
#include <xworkspace/io.h>
#include <xworkspace/string.h>
#include <xworkspace/ram.h>
#include <xworkspace/pic.h>
#include <xworkspace/systables.h>
#include <xworkspace/igates.h>
#include <xworkspace/task.h>
#include <xworkspace/vconsole.h>





extern void task_entry0();
Task task0;

extern void task_entry1();
Task task1;

extern void task_entry2();
Task task2;

extern void task_entry3();
Task task3;

extern void task_entry4();
Task task4;

extern void task_entry5();
Task task5;

extern void task_entry6();
Task task6;

extern void task_entry7();
Task task7;









void xmain()
{
  inizTask( &task0, TSS_ENTRY(1) );
  addTask( &task0, (u32) &task_entry0, 0x9FFFF-1024*1 );
  inizTask( &task1, TSS_ENTRY(2) );
  addTask( &task1, (u32) &task_entry1, 0x9FFFF-1024*2 );
  inizTask( &task2, TSS_ENTRY(3) );
  addTask( &task2, (u32) &task_entry2, 0x9FFFF-1024*3 );
  inizTask( &task3, TSS_ENTRY(4) );
  addTask( &task3, (u32) &task_entry3, 0x9FFFF-1024*4 );
  inizTask( &task4, TSS_ENTRY(5) );
  addTask( &task4, (u32) &task_entry4, 0x9FFFF-1024*5 );
  inizTask( &task5, TSS_ENTRY(6) );
  addTask( &task5, (u32) &task_entry5, 0x9FFFF-1024*6 );
  inizTask( &task6, TSS_ENTRY(7) );
  addTask( &task6, (u32) &task_entry6, 0x9FFFF-1024*7 );
  inizTask( &task7, TSS_ENTRY(8) );
  addTask( &task7, (u32) &task_entry7, 0x9FFFF-1024*8 );

  STI();
  for(;;)  HLT();
};








ASM("_task_entry0:        ;"
    "  mov $0xB80A0, %edi ;"
    "  jmp 1f             ;"
    "_task_entry1:        ;"
    "  mov $0xB8140, %edi ;"
    "  jmp 1f             ;"
    "_task_entry2:        ;"
    "  mov $0xB81E0, %edi ;"
    "  jmp 1f             ;"
    "_task_entry3:        ;"
    "  mov $0xB8280, %edi ;"
    "  jmp 1f             ;"
    "_task_entry4:        ;"
    "  mov $0xB8320, %edi ;"
    "  jmp 1f             ;"
    "_task_entry5:        ;"
    "  mov $0xB83C0, %edi ;"
    "  jmp 1f             ;"
    "_task_entry6:        ;"
    "  mov $0xB8460, %edi ;"
    "  jmp 1f             ;"
    "_task_entry7:        ;"
    "  mov $0xB8500, %edi ;"
    "  jmp 1f             ;"
    "1:                   ;"
    "  mov $0x4, %ah      ;"
    "2:                   ;"
    "  hlt                ;"
    "  mov $'0', %al      ;"
    "  mov $80, %ecx      ;"
    "  rep                ;"
    "  stosw              ;"
    "  sub $160, %edi     ;"
    "  hlt                ;"
    "  mov $'1', %al      ;"
    "  mov $80, %ecx      ;"
    "  rep                ;"
    "  stosw              ;"
    "  sub $160, %edi     ;"
    "  hlt                ;"
    "  jmp 1b             ;");


u8 keysAlpha[] =       {
                         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                         0,  0,  0,  0,  0,  0,  1,  1,  1,  1,
                         1,  1,  1,  1,  1,  1,  0,  0,  0,  0,
                         1,  1,  1,  1,  1,  1,  1,  1,  1,  0,
                         0,  0,  0,  0,  1,  1,  1,  1,  1,  1,
                         1,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                         0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
                       };


tchar keys[] =         {
                         '\0',  '\0',  '1',   '2',   '3',   '4',   '5',   '6',   '7',   '8',
                         '9',   '0',   '-',   '=',   '\b',  '\t',  'q',   'w',   'e',   'r',
                         't',   'y',   'u',   'i',   'o',   'p',   '[',   ']',   '\n',  '\0',
                         'a',   's',   'd',   'f',   'g',   'h',   'j',   'k',   'l',   ';',
                         '\'',  '`',   '\0',  '\\',  'z',   'x',   'c',   'v',   'b',   'n',
                         'm',   ',',   '.',   '/',   '\0',  '\0',  '\0',  ' ',   '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                       };


tchar keysShifted[] =  {
                         '\0',  '\0',  '!',   '@',   '#',   '$',   '%',   '^',   '&',   '*',
                         '(',   ')',   '_',   '+',   '\b',  '\t',  'Q',   'W',   'E',   'R',
                         'T',   'Y',   'U',   'I',   'O',   'P',   '{',   '}',   '\n',  '\0',
                         'A',   'S',   'D',   'F',   'G',   'H',   'J',   'K',   'L',   ':',
                         '\"',  '~',   '\0',  '|',   'Z',   'X',   'C',   'V',   'B',   'N',
                         'M',   '<',   '>',   '?',   '\0',  '\0',  '\0',  ' ',   '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                         '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',  '\0',
                       };


static u8 shiftState = 0;
static u8 capsLockState = 0;

void doOnIRQ1( u8 scancode )
{
  switch( scancode & 0x7F )
  {
  case 42:
  case 54:
    shiftState = !(scancode & 0x80);
    break;

  case 0x3A:
    capsLockState = !capsLockState;
    return;

  default:
    if( scancode & 0x80 )  return;
    if( capsLockState )
    {
      vcprint( (shiftState ^ keysAlpha[scancode]) ? keysShifted[scancode] : keys[scancode] );
    } else {
      vcprint( shiftState ? keysShifted[scancode] : keys[scancode] );
    };
  };
};
