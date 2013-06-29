/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

// mbs (stage0)
.include "config.asm"





.text
.code16
.global mbs




mbs:
// switch from 07C0:0000 to 0000:7C00
	ljmp $mbsSEGMENT, $run

message:
	.asciz "[andromeda:mbs execution]\n\r"

run:
// set up the segment-registers
	movw %cs, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %gs
	movw %ax, %fs

// stack grows from 07C0:0000 (0000:7C00)
	xorw %sp, %sp

// clear screen
	movw $0x03, %ax
	int $0x10

// set solid cursor
	//movb $0x01, %ah
	//movb $0x1F, %cl
	//movb $0x00, %ch
	//int $0x10

// set 640x350 G-mode
	//movw $0x0010, %ax
	//int $0x10

// vga text mode. Font 8x8 50 lines
	//movw $0x1112, %ax
	//mov $0x00, %bl
	//int $0x10

// hi-resolution
	//movw $0x4F02, %ax
	//movw $0x11A, %bx
	//int $0x10

// first message
	mov $message, %si
	call echo

// EDD presence detection
	movb $0x41, %ah
// 1st drive
	movb $0x80, %dl
// ???, but needed
	movw $0x55AA, %bx
	int $0x13
	jc failed

// EDD read sectors
	movb $0x42, %ah
// 1st drive
	movb $0x80, %dl
// see `dap` below
	mov $dap, %si
	int $0x13
	jc failed

// check RMS signature
	mov $rmsSEGMENT, %ax
	mov %ax, %es
	movw %es:(rmsSIZE-2), %ax
	cmp $rmsSIGNATURE, %ax
	jne failed

// masking interrupts
	cli
	mov $0xFF, %al
	outb %al, $0x21
	outb %al, $0xA1

// disable nmi
	in  $0x70, %al
	or  $0x80, %al
	out %al, $0x70

// jump to real-mode initialization code
	ljmp $rmsSEGMENT, $0x0










// boot failed
failed:
	int $0x18


// echoes the text from %si
echo:
	cld
	movb $0x0E, %ah
1:
	lodsb
	testb %al, %al
	jz 2f
	int $0x10
	jmp 1b
2:
	ret







// resources
dap:
// DAP size = 16 bytes
.byte 0x10
// reserved
.byte 0x00
// number of sectors for read (48)
.byte 0x30
// reserved
.byte 0x00
// memory offset
.word 0x0000
// memory segment
.word sysSEGMENT
// first sector for read
.long 0x00000001
.long 0x00000000




//.org didOFFSET
// disk identifier
// ...

.org mptOFFSET
// main partition table
// ...


.org mbsSIZE-2
// mbs signature
.word mbsSIGNATURE
