/**
 * @target: os xworkspace
 * @author: Krutko Vitaliy
 * @aka: asmforce
 * @e-mail: asmforce@ukr.net
 * @copyright (C)
**/

/**
 * There are primary inerrupt handlers
 * declared in this file. Primary handlers
 * calls secondary handlers, if needed.
**/
.intel_syntax
.intel_mnemonic
.arch i486

.text
.code32
.global _onIRQ0, _onIRQ1

_onIRQ0:
push eax
push ebx
push ecx
push edx
push ebp
push esi
push edi
call _doOnIRQ0
pop edi
pop esi
pop ebp
pop edx
pop ecx
pop ebx
pop eax
sti
iret

_onIRQ1:
pusha
xor eax, eax
mov dx, 0x60
in al, dx
push eax
call _doOnIRQ1
pop eax
popa
sti
iret

mark: .byte 0
