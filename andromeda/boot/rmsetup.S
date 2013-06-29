/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

// rms (real-mode setup - stage1)
.include "config.asm"





.text
.code16
.global rms




rms:
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %es
	movw %ax, %gs
	movw %ax, %fs

// stack from 9000:FC00 to 9000:0000
	movw $0x9000, %ax
	movw %ax, %ss
	movw $0xFC00, %sp

// copy system GDT entries to $gdtADDRESS
	xorw %ax, %ax
	movw %ax, %es
	movw $gdtADDRESS, %di
	movw $GDT, %si
	movw $(gdtSYSENTRIES * dscSIZE/2), %cx
	rep movsw

// clean unused entries (just in case)
	xorw %ax, %ax
	movw $((gdtENTRIES-gdtSYSENTRIES) * dscSIZE/2), %cx
	rep stosw

// load GDTR and IDTR
	lgdt GDTR
	lidt IDTR

// open a20 gate
	in  $0x92, %al
	or  $0x02, %al
	out %al, $0x92

// enable protection
	mov %cr0, %eax
	or  $0x01, %eax
	mov %eax, %cr0

// storing selector to segment registers
	movw  $dataSELECTOR, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %gs
	movw %ax, %fs

// far jump to 32-bits code, protected mode setup
	ljmp $codeSELECTOR, $pmsADDRESS









// interrupt descriptor table register
IDTR:
.word idtLIMIT
.long idtADDRESS


// global descriptor table register
GDTR:
.word gdtLIMIT
.long gdtADDRESS



// global descriptor table
GDT:
// null descriptor (needed for compatibility)
.byte 0,0,0,0,0,0,0,0

// code, 32-bits, 4gb, present, ring0
.word 0xFFFF
.byte 0, 0, 0
.byte 0b10011010
.byte 0b11001111
.byte 0

// data, 32-bits, 4gb, present, ring0
.word 0xFFFF
.byte 0, 0, 0
.byte 0b10010010
.byte 0b11001111
.byte 0








.org rmsSIZE-2
// rms signature
.word rmsSIGNATURE
