/**
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

// Primary boot-loader

.intel_syntax
.intel_mnemonic
.arch i486
.include "config.h"
















.text
.code16
.global entry





entry:
ljmp BOOT_SEGMENT, offset boot

boot:
// Initialize registers
mov ax, cs
mov ds, ax
mov es, ax
mov ss, ax
mov sp, 0xFFFF

// VGA text mode. Font 8x8. 50 lines
mov ax, 0x1112
mov bl, 0x00
int 0x10

// Prompt-message
mov si, offset msgLoadingStarts
call print

// EDD presence detection
mov ah, 0x41
// 1st drive
mov dl, 0x80
// ???, but needed
mov bx, 0x55AA
int 0x13
jc loadingFailed

// EDD read sectors
mov ah, 0x42
// 1st drive
mov dl, 0x80
// see `DAP` below
mov si, offset DAP
int 0x13
jc loadingFailed

// Loading by func 2 of int 0x13
// cylinder 0, head 0, track 0, sector 2
//mov ax, SYSTEM_SEGMENT
//mov es, ax
//mov dx, 0x0000
//mov cx, 0x0002
//mov bx, 0x0000
//mov al, SYSTEM_SECTORS
//mov ah, 0x02
//int 0x13

// Is success?
jc loadingFailed

// Masking interrupts
cli
mov al, 0xFF
out 0x21, al
out 0xA1, al

// Disable NMI
in  al, 0x70
or  al, 0x80
out 0x70, al


// Print message
mov si, offset msgSetupJump
call print


// Jump to 16-bit setup
ljmp 0, INIT16_ADDRESS









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



loadingFailed:
mov si, offset msgLoadingFailed
call print
call waitKbd
call reboot



waitKbd:
mov ah, 0x10
int 0x16
ret



reboot:
mov al, 0xFE
out 0x64, al
1:
jmp 1b





msgLoadingStarts:  .asciz "#OS XWorkSpace (kernel-0.01) Loading...\n\r\n\r"
msgSetupJump:      .asciz "#Real Mode Setup\n\r"
msgLoadingFailed:  .asciz "#Loading failed\n\r#Press any key to reboot"
msgEDDNotPresent:  .asciz "#Error: EDD not present"
exeFlag:           .byte 0x00

DAP:
// DAP size = 16 bytes
.byte 0x10
// reserved
.byte 0x00
// number of sectors for read (16)
.byte 0x10
// reserved
.byte 0x00
// memory offset
.word 0x0000
// memory segment
.word SYSTEM_SEGMENT
// first sector for read
.long 0x00000001
.long 0x00000000

// .org 0x1BE
// MBR partition table

.org 0x1FE
// MBR signature
.word BOOT_SIGNATURE
