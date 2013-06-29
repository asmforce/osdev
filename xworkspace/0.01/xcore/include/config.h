/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

#ifndef XWORKSPACE_CONFIG_H
#define XWORKSPACE_CONFIG_H

#pragma pack(1)

#define ALWAYS_INLINE __attribute__((__always_inline__))

// Inline assembler
#define ASM __asm__

#define SET_INTEL_ASM()    \
ASM(".intel_syntax   ;"    \
    ".intel_mnemonic ;")   \

#define SET_ATT_ASM()      \
ASM(".att_syntax   ;"      \
    ".att_mnemonic ;")     \

// Choose i486 architecture
ASM(".arch i486");

#define CLI()    ASM("cli")
#define STI()    ASM("sti")
#define NOP()    ASM("nop")
#define HLT()    ASM("hlt")

#define PUSHA()  ASM("pusha")
#define POPA()   ASM("popa")
#define PUSHF()  ASM("pushf")
#define POPF()   ASM("popf")

#define LTR( s ) ASM("ltr %%ax" :: "a" (s));

#define CPUID( eax, ebx, ecx, edx )              \
ASM("cpuid;"                                     \
: "=a" (eax),                                    \
  "=b" (ebx),                                    \
  "=c" (ecx),                                    \
  "=d" (edx)                                     \
: "a" (eax) )


// Declare smart typenames
typedef unsigned char        tchar;
typedef unsigned short       wchar;

typedef signed char          i8;
typedef unsigned char        u8;

typedef signed short         i16;
typedef unsigned short       u16;

typedef signed int           i32;
typedef unsigned int         u32;

typedef signed long long     i64;
typedef unsigned long long   u64;

#endif
