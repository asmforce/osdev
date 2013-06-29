/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/

.code32
//.include "include/task.def"





.globl _onDivideError
.globl _onDebug
.globl _onNmi
.globl _onBreakpoint
.globl _onOverflow
.globl _onBoundsExceeded
.globl _onInvalidOpcode
.globl _onNoX87
.globl _onDoubleFault
.globl _onX87Overrun
.globl _onInvalidTss
.globl _onSegmentNotPresent
.globl _onStackSegmentFault
.globl _onGeneralProtection
.globl _onPageFault
.globl _onReserved
.globl _onX87Fault
.globl _onAlignmentCheck





.set TASK_ERROR_NONE,                0x00
.set TASK_ERROR_DIVIDE,              0x01
.set TASK_ERROR_DEBUG,               0x02
.set TASK_ERROR_NMI,                 0x03
.set TASK_ERROR_BREAKPOINT,          0x04
.set TASK_ERROR_OVERFLOW,            0x05
.set TASK_ERROR_BOUNDS_EXCEEDED,     0x06
.set TASK_ERROR_INVALID_OPCODE,      0x07
.set TASK_ERROR_NO_X87,              0x08
.set TASK_ERROR_DOUBLE_FAULT,        0x09
.set TASK_ERROR_X87_OVERRUN,         0x0A
.set TASK_ERROR_INVALID_TSS,         0x0B
.set TASK_ERROR_SEGMENT_NOT_PRESENT, 0x0C
.set TASK_ERROR_STACK_SEGMENT_FAULT, 0x0D
.set TASK_ERROR_GENERAL_PROTECTION,  0x0E
.set TASK_ERROR_PAGE_FAULT,          0x0F
.set TASK_ERROR_RESERVED,            0x10
.set TASK_ERROR_X87_FAULT,           0x11
.set TASK_ERROR_ALIGNMENT_CHECK,     0x12


/*
_rdio8:
	push %eax
	push %dx
	add $10, %esp
	
	sub $10, %esp
	pop %dx
	pop %eax
	ret
*/



.align 4
_onDivideError:
	cli
	push $msgDivideError
	call _prints
	add $4, %esp
	pushl TASK_ERROR_DIVIDE
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onDebug:
	cli
	push $msgDebug
	call _prints
	add $4, %esp
	pushl TASK_ERROR_DEBUG
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onNmi:
	cli
	push $msgNmi
	call _prints
	add $4, %esp
	pushl TASK_ERROR_NMI
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onBreakpoint:
	cli
	push $msgBreakpoint
	call _prints
	add $4, %esp
	pushl TASK_ERROR_BREAKPOINT
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onOverflow:
	cli
	push $msgOverflow
	call _prints
	add $4, %esp
	pushl TASK_ERROR_OVERFLOW
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onBoundsExceeded:
	cli
	push $msgBoundsExceeded
	call _prints
	add $4, %esp
	pushl TASK_ERROR_BOUNDS_EXCEEDED
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onInvalidOpcode:
	cli
	push $msgInvalidOpcode
	call _prints
	add $4, %esp
	pushl TASK_ERROR_INVALID_OPCODE
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onNoX87:
	cli
	push $msgNoX87
	call _prints
	add $4, %esp
	pushl TASK_ERROR_NO_X87
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onDoubleFault:
	//( u32 errcode )
	cli
	push $msgDoubleFault
	call _prints
	add $4, %esp
	pushl TASK_ERROR_DOUBLE_FAULT
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onX87Overrun:
	cli
	push $msgX87Overrun
	call _prints
	add $4, %esp
	pushl TASK_ERROR_X87_OVERRUN
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onInvalidTss:
	//( u32 errcode )
	cli
	push $msgInvalidTss
	call _prints
	add $4, %esp
	pushl TASK_ERROR_INVALID_TSS
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onSegmentNotPresent:
	//( u32 errcode )
	cli
	push $msgSegmentNotPresent
	call _prints
	add $4, %esp
	pushl TASK_ERROR_SEGMENT_NOT_PRESENT
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onStackSegmentFault:
	//( u32 errcode )
	cli
	push $msgStackSegmentFault
	call _prints
	add $4, %esp
	pushl TASK_ERROR_STACK_SEGMENT_FAULT
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onGeneralProtection:
	//( u32 errcode )
	cli
	push $msgGeneralProtection
	call _prints
	add $4, %esp
	pushl TASK_ERROR_GENERAL_PROTECTION
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onPageFault:
	//( u32 errcode )
	cli
	push $msgPageFault
	call _prints
	add $4, %esp
	pushl TASK_ERROR_PAGE_FAULT
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onReserved:
	cli
	push $msgReserved
	call _prints
	add $4, %esp
	pushl TASK_ERROR_RESERVED
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onX87Fault:
	cli
	push $msgX87Fault
	call _prints
	add $4, %esp
	pushl TASK_ERROR_X87_FAULT
	call _onTaskFault
	add $4, %esp
	sti
	iret

.align 4
_onAlignmentCheck:
	//( u32 errcode )
	cli
	push $msgAlignmentCheck
	call _prints
	add $4, %esp
	pushl TASK_ERROR_ALIGNMENT_CHECK
	call _onTaskFault
	add $4, %esp
	sti
	iret




msgDivideError:        .asciz "[Exception:DivideError]\n"
msgDebug:              .asciz "[Exception:Debug]\n"
msgNmi:                .asciz "[Exception:NMI]\n"
msgBreakpoint:         .asciz "[Exception:Breakpoint]\n"
msgOverflow:           .asciz "[Exception:Overflow]\n"
msgBoundsExceeded:     .asciz "[Exception:BoundsExceeded]\n"
msgInvalidOpcode:      .asciz "[Exception:InvalidOpcode]\n"
msgNoX87:              .asciz "[Exception:NoX87]\n"
msgDoubleFault:        .asciz "[Exception:DoubleFault]\n"
msgX87Overrun:         .asciz "[Exception:X87Overrun]\n"
msgInvalidTss:         .asciz "[Exception:InvalidTSS]\n"
msgSegmentNotPresent:  .asciz "[Exception:SegmentNotPresent]\n"
msgStackSegmentFault:  .asciz "[Exception:StackSegmentFault]\n"
msgGeneralProtection:  .asciz "[Exception:GeneralProtection]\n"
msgPageFault:          .asciz "[Exception:PageFault]\n"
msgReserved:           .asciz "[Exception:Reserved]\n"
msgX87Fault:           .asciz "[Exception:X87Fault]\n"
msgAlignmentCheck:     .asciz "[Exception:AlignmentCheck]\n"
