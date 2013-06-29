/**
 * Базовая инициализация в защищенном режиме
 * asmforce (nickname) asmforce@ukr.net
 * 2010
**/






.code32
.globl init32




init32:
/**
 *  Инициализация PIC
 *  ICW1 Команда инициализации, Используется ICW4
 *
 *  ICW2 Начальные вектора прерываний
 *
 *  ICW3 Для ведущего - биты, установленные в 1
 *  указывают на подключеный ведомый PIC.
 *  Для ведомого - биты [2:0] указывают индекс входа
 *  ведущего контроллера, к которой он подключен
 *
 *  ICW4 Процессор 8088/8086+. Включено AEOI
**/

// Инициализация ведущего контроллера
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

// Инициализация ведомого контроллера
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
