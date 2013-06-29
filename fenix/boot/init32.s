/**
 * ������� ������������� � ���������� ������
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/






.code32
.globl init32




init32:
/**
 *  ������������� PIC
 *  ICW1 ������� �������������, ������������ ICW4
 *
 *  ICW2 ��������� ������� ����������
 *
 *  ICW3 ��� �������� - ����, ������������� � 1
 *  ��������� �� ����������� ������� PIC.
 *  ��� �������� - ���� [2:0] ��������� ������ �����
 *  �������� �����������, � ������� �� ���������
 *
 *  ICW4 ��������� 8088/8086+. �������� AEOI
**/

// ������������� �������� �����������
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

// ������������� �������� �����������
	mov $0xA0, %dx
	mov $0x11, %al
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

ret
