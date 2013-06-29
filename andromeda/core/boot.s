/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

.include "boot/config.hpp"




.text
.global start, _IDT, _GDT

start:
	jmp setup



.align 4
// multiboot head structure
head:
	.long MBOOT_MAGIC
	.long MBOOT_FLAGS
	.long -(MBOOT_MAGIC + MBOOT_FLAGS)
	.long head
	.long start
	.long _end
	.long _end
	.long setup



setup:
// initialize stack
	movl $(stack + STACK_SIZE), %esp

// info from bootloader
	movl %ebx, mbinfo
	movl %eax, mbeax

// copy gdt to 0x500 address
	movl $GDT, %esi
	movl $GDT_ADDRESS, %edi
// three entries: `null`, `code` and `data`
	movl $(DSC_SIZE * 3), %ecx
	rep movsb

// cleanup other gdt entries
	movl $(DSC_SIZE * (GDT_ENTRIES-3)), %ecx
	xorl %eax, %eax
	rep stosb

// initialize idt
	movl $IDT_ADDRESS, %edi
	movl $(DSC_SIZE * IDT_ENTRIES), %ecx
	xorl %eax, %eax
	rep stosb

// load GDTR and IDTR
	lgdt GDTR
	lidt IDTR

// reloading segment registers
	ljmp $CODE_DSC, $systables_reconfig

systables_reconfig:
	movw $DATA_DSC, %ax
	movw %ax, %ds
	movw %ax, %ss
	movw %ax, %es
	movw %ax, %fs
	movw %ax, %gs

// setup stack
	movl $0x9FC00, %esp

// enable nmi
	in $0x70, %al
	and $0x7F, %al
	out %al, $0x70

// setup master pic
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

// setup slave pic
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

// reset eflags
	pushl $0x0
	popf

// masking interrupts
	cli
	mov $0xFF, %al
	outb %al, $0x21
	outb %al, $0xA1

	movl mbinfo, %ebx
	pushl %ebx
	movl mbeax, %eax
	pushl %eax
	call _setup

1:
	hlt
	jmp 1b




// mbi address
mbinfo:
	.long 0x0

// eax must contain magic value
mbeax:
	.long 0x0


// interrupt descriptor table register
IDTR:
	.word IDT_LIMIT
_IDT:
	.long IDT_ADDRESS


// global descriptor table register
GDTR:
	.word GDT_LIMIT
_GDT:
	.long GDT_ADDRESS


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




.bss
// stack area
	.comm stack, STACK_SIZE
