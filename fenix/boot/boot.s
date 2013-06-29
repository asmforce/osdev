/**
 * ��������� �� ������ (Fenix)
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/









.set SectorSize,    512
.set LoaderAddress, 0x7C00

.set GdtSize,       (256 * 8)
.set IdtSize,       (256 * 8)

.set GdtAddress,    0xD00
.set IdtAddress,    0x500

.set KernelAddress, (LoaderAddress + SectorSize)
.set KernelSectors, 64





jmp rmmain




.code16
// ������ �������� ����
loadingFailed:
	mov $loadingFailedMessage, %esi
	call print

	mov $0x10, %ah
	int $0x16

	mov $0xFE, %al
	out %al, $0x64

.waitReboot:
	jmp .waitReboot




// ��������� ������ ������, �� ������ esi � �������
print:
	mov $0x0E, %ah
.printLoop:
	lodsb
	test %al, %al
	jz .exitPrint
	int $0x10
	jmp .printLoop
.exitPrint:
ret








.code16
//-----------------------------------------------------real mode-----------------------------------------------------
rmmain:
// ������������� ���������
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov $LoaderAddress, %sp


// ������������ ����� 8x8 VGA. 50 �����
	mov $0x1112, %ax
	mov $0x00,   %bl
	int $0x10


// ������� ������ �����������
	mov $loadingStartedMessage, %si
	call print


// ��������� ����. ���������� ������� 2 ���������� 0x13
// ������� 0, ������� 0, ������� 0, ������ 2. �.�.
// ������ ���� � �������, � � ������ ������� ���������
	mov $0x00, %dl
	mov $0x00, %dh
	mov $0x00, %ch
	mov $0x02, %cl
	mov $KernelSectors, %al
	mov $KernelAddress, %bx

	mov $0x02, %ah
	int $0x13
// ��������� ���������� ����������
	jc loadingFailed


// ��������� ��� ����������.
	cli
	mov $0xFF, %al
	out %al, $0x21
	out %al, $0xA1


// ��������� ������������� ����������
	in  $0x70, %al
	or  $0x80, %al
	out %al,   $0x70


// ����������� GDT �� ������ 0xD00
	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %es
	mov $0xD00, %di
	mov $gdt, %si

// 24 ����� - 3 8��-������� �����������: �������, ���� � ������
	mov $24, %cx
	rep movsb


// �������� ��������� GDT, IDT
	lgdt gdtr
	lidt idtr


// ��������� �������� ����� A20
	in  $0x92, %al
	or  $0x02, %al
	out %al, $0x92


// �������� ������. �.�. PM
	mov %cr0, %eax
	or  $0x01, %eax
	mov %eax, %cr0


// ������� �������� � ���������� ��������
	mov  $0x10, %ax
	mov  %ax, %ds
	mov  %ax, %ss
	mov  %ax, %es
	mov  %ax, %fs
	mov  %ax, %gs


// ��������� ������� ������, ��� ���������
// ��������� ������� ����� ����������� �������� cs
// � ������� � 32-� ������ ���
	ljmp $0x08, $pmmain











.code32
//---------------------------------------------------protected mode--------------------------------------------------
pmmain:
// ������������� ��������� �����
	mov $0x9FFFF, %esp

// �������� ������������� ����������
	in $0x70, %al
	and $0x7F, %al
	out %al, $0x70

// ������������� � ���������� ������
	call init32

// ������� � ��� ����
	jmp _osmain









/**
 * ���������� ������� ������������
 * ����� ��������� ������ ������ ���
 * �����������. ����� ��������� � PM
 * ��� ����� ����������� �� ������ 0xD00
 *
 * ��������� �����������:
 * ���� 0,1:   �����
 * ���� 2,3,4: ���� [0-23]
 * ���� 5:     (0-��� �����������) (00-������� ������� ����������) (0-���������� [�������] ���� ��� ������) (1010-��� ��� ����������/������, 0010-������ ��� ������/������)
 * ���� 6:     (0-��� �������������) (0-32-� ������ �������) (0-������ ���� ����) (0-�� ����� ��������, ����������������) (0000-�����)
 * ���� 7:     ���� [24-31]
**/

gdt:
// ������� ����������. ����������
	.byte 0,0,0,0,0,0,0,0

// ���������� ���� 4GB
	.word 0xFFFF
	.byte 0, 0, 0
	.byte 0b10011010
	.byte 0b11001111
	.byte 0

// ���������� ������ 4GB
	.word 0xFFFF
	.byte 0, 0, 0
	.byte 0b10010010
	.byte 0b11001111
	.byte 0

gdtr:
.word GdtSize-1
.long GdtAddress










/**
 * ������� ������������ ����������
 * ��� ����������� ����� ������������
 * �� ���� ����
 *
 * ��������� ���� ������� �����������
 * � ������� 0x500-0xCFF, ����� ��
 * ��������� ������ �������� �������� IDTR
**/
idtr:
.word IdtSize-1
.long IdtAddress









loadingStartedMessage: .ascii "                              [OS Fenix (c) kernel]                             \0"

loadingFailedMessage:  .ascii "                             Fatal:  Loading Failed                             "
                       .ascii "                            Press any key for reboot                            \0"


/**
 * ��������� .org ������������ ��� ������������
 * �������� ���������� �� 512 ���� ������������
 * �������. ����� ������� ��������� ����������,
 * 0xAA55. ��� ����� ����������� BIOS.
**/

.org 510

signature:
.word 0xAA55
