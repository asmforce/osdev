/**
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

// Secondary loader

.intel_syntax
.intel_mnemonic
.arch i486
.include "src/config.h"
















.text
.code16
.global init16






init16:
// Setup registers
mov ax, cs
mov es, ax
mov ds, ax
mov ss, ax

mov si, offset msgSetup
call print

// Copying GDT to address GdtAddress
mov ax, 0
mov es, ax
mov di, GDT_ADDRESS
mov si, offset GDT
mov cx, 24
rep movsb

// Load GDTR and IDTR
lgdt GDTR
lidt IDTR

// Open A20 gate
in  al, 0x92
or  al, 0x02
out 0x92, al

// Enable protect
mov eax, cr0
or  eax, 0x01
mov cr0, eax

// Storing selector to segment registers
mov  ax, 0x10
mov  ds, ax
mov  es, ax
mov  ss, ax
mov  fs, ax
mov  gs, ax

ljmp 0x08, INIT32_ADDRESS










print:
cld
mov ah, 0x0E
1:
lodsb
test al, al
jz 2f
int 0x10
jmp 1b
2:
ret











/**
 * GDT (Global Descriptor Table)
 * Later will be copied to GdtAddress
**/
GDT:
// Null descriptor
.byte 0,0,0,0,0,0,0,0

// Code 4GB
.word 0xFFFF
.byte 0, 0, 0
.byte 0b10011010
.byte 0b11001111
.byte 0

// Data 4GB
.word 0xFFFF
.byte 0, 0, 0
.byte 0b10010010
.byte 0b11001111
.byte 0

GDTR:
.word GDT_SIZE-1
.long GDT_ADDRESS








/**
 * IDT (Interrupt Descriptor Table) Register
 * IDT will be located at 0x500+GdtSize
**/
IDT:
IDTR:
.word IDT_SIZE-1
.long IDT_ADDRESS






msgSetup: .asciz "#System initialization\n\r#Enabling 32-bit mode\n\r\n\r"
