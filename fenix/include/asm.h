/**
 * os fenix
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/
#ifndef FENIX_ASM_H
#define FENIX_ASM_H

#include "aliases.h"

#define CLI()    ASM("cli")
#define STI()    ASM("sti")
#define NOP()    ASM("nop")
#define HLT()    ASM("hlt")

#define PUSHA()  ASM("pusha")
#define POPA()   ASM("popa")
#define PUSHF()  ASM("pushf")
#define POPF()   ASM("popf")

#define machineReboot() ASM("mov $0xFE, %al    \n"  \
                            "out %al, $0x64    \n"  \
                            "mark: \t jmp mark \n")

#define CPUID( _eax_, _ebx_, _ecx_, _edx_ )  ASM("cpuid":"=a"(_eax_),"=b"(_ebx_),"=c"(_ecx_),"=d"(_edx_):"a"(_eax_))
 
#define MAKE_ASM_CALL( cname, asmname )   \
extern void asmname();                    \
ASM("_" #asmname     ": ;"                \
    "call _" #cname  "  ;"                \
    "iret               ;"); 

#define MAKE_ASM_CALL_ERROR( cname, asmname )   \
extern void asmname();                          \
ASM("_" #asmname     ":    ;"                   \
        "call _" #cname  " ;"                   \
        "add $4, %esp      ;"                   \
        "iret              ;");
 
#define MAKE_ASM_TASK_CALL( cname, asmname )   \
extern void asmname();                         \
ASM("_" #asmname     ":     ;"                 \
        "call _" #cname  "  ;"                 \
        "1:                 ;"                 \
        "hlt                ;"                 \
        "jmp 1b             ;");

#endif
