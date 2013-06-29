/**
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/


// Tertiary loader

.intel_syntax
.intel_mnemonic
.arch i486
.include "config.h"









.text
.code32
.global init32




init32:
// Enable NMI
in al, 0x70
and al, 0x7F
out 0x70, al

// Initialize master PIC
mov dx, 0x20
mov al, 0x11
out dx, al
inc dx
mov al, 0x20
nop
out dx, al
mov al, 0x04
nop
out dx, al
mov al, 0x03
nop
out dx, al

// Initialize slave PIC
mov dx, 0xA0
mov al, 0x11
out dx, al
inc dx
mov al, 0x28
nop
out dx, al
mov al, 0x02
nop
out dx, al
mov al, 0x03
nop
out dx, al

// Setup stack
mov esp, 0x9FFFF

pushd GDT_ADDRESS
pushd IDT_ADDRESS
call _iniz
add esp, 8
call _xmain

// Just in case :)
0:
hlt
jmp 0b
