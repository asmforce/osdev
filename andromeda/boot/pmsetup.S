/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

// pms (protected-mode setup - stage1)
.include "config.asm"





.text
.code32
.global pms
.extern _setup
.extern _cppmain



pms:
// setup stack
	movl $0x9FC00, %esp

// enable nmi
	in $0x70, %al
	and $0x7F, %al
	out %al, $0x70

// Инициализация ведущего контроллера
	mov $0x20, %dx
	mov $0x11, %al
	out %al, %dx
	inc %dx
	mov $0x20, %al
	nop
	out %al, %dx
	mov $0x04, %al
	nop
	out %al, %dx
	mov $0x03, %al
	nop
	out %al, %dx

// Инициализация ведомого контроллера
	mov $0xA0, %dx
	mov $0x11, %al
	nop
	out %al, %dx
	inc %dx
	mov $0x28, %al
	nop
	out %al, %dx
	mov $0x02, %al
	nop
	out %al, %dx
	mov $0x03, %al
	nop
	out %al, %dx

// main setup stage
	pushl $gdtADDRESS
	pushl $idtADDRESS
	call _setup
	addl $0x8, %esp
	call _cppmain

// just in case
1:
	hlt
	jmp 1b
