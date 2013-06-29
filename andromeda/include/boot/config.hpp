/**
 * @project Andromeda
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

// andromeda core stack size
.equ STACK_SIZE,  0x8000

// multiboot magic value
.equ MBOOT_MAGIC, 0x1BADB002

// multiboot flags
.equ MBOOT_FLAGS, 0x00000000

// multiboot convention
.equ MBOOT_EAX,   0x2BADB002



// idt/gdt descriptor size
.equ DSC_SIZE, 0x08

// interrupt descriptor table
.equ IDT_ADDRESS, 0x500
.equ IDT_SEGMENT, (IDT_ADDRESS / 0x10)

.equ IDT_ENTRIES, 0x100
.equ IDT_SIZE, (IDT_ENTRIES * DSC_SIZE)
.equ IDT_LIMIT, (IDT_SIZE - 1)

// global descriptor table
.equ GDT_ADDRESS, (IDT_ADDRESS + IDT_SIZE)
.equ GDT_SEGMENT, (GDT_ADDRESS / 0x10)

.equ GDT_ENTRIES, 0x100
.equ GDT_SIZE, (GDT_ENTRIES * DSC_SIZE)
.equ GDT_LIMIT, (GDT_SIZE - 1)

// system selectors
.equ CODE_DSC, 0x08
.equ DATA_DSC, 0x10
