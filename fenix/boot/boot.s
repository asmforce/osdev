/**
 * Загрузчик ОС Феникс (Fenix)
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
// Ошибка загрузки ядра
loadingFailed:
	mov $loadingFailedMessage, %esi
	call print

	mov $0x10, %ah
	int $0x16

	mov $0xFE, %al
	out %al, $0x64

.waitReboot:
	jmp .waitReboot




// Процедура вывода строки, по адресу esi в консоль
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
// Инициализация регистров
	mov %cs, %ax
	mov %ax, %ds
	mov %ax, %es
	mov %ax, %ss
	mov $LoaderAddress, %sp


// Использовать шрифт 8x8 VGA. 50 строк
	mov $0x1112, %ax
	mov $0x00,   %bl
	int $0x10


// Выводим строку приветствия
	mov $loadingStartedMessage, %si
	call print


// загружаем ядро. используем функцию 2 прерывания 0x13
// цилиндр 0, головка 0, дорожка 0, сектор 2. т.к.
// отсчет идет с единицы, а в первом секторе загрузчик
	mov $0x00, %dl
	mov $0x00, %dh
	mov $0x00, %ch
	mov $0x02, %cl
	mov $KernelSectors, %al
	mov $KernelAddress, %bx

	mov $0x02, %ah
	int $0x13
// Проверяем успешность считывания
	jc loadingFailed


// Маскируем все прерывания.
	cli
	mov $0xFF, %al
	out %al, $0x21
	out %al, $0xA1


// Отключаем немаскируемые прерывания
	in  $0x70, %al
	or  $0x80, %al
	out %al,   $0x70


// Копирование GDT по адресу 0xD00
	xor %ax, %ax
	mov %ax, %ds
	mov %ax, %es
	mov $0xD00, %di
	mov $gdt, %si

// 24 Байта - 3 8ми-байтных дескриптора: нулевой, кода и данных
	mov $24, %cx
	rep movsb


// Загрузка регистров GDT, IDT
	lgdt gdtr
	lidt idtr


// Включение адресной линии A20
	in  $0x92, %al
	or  $0x02, %al
	out %al, $0x92


// Включаем защиту. т.е. PM
	mov %cr0, %eax
	or  $0x01, %eax
	mov %eax, %cr0


// Заносим селектор в сегментные регистры
	mov  $0x10, %ax
	mov  %ax, %ds
	mov  %ax, %ss
	mov  %ax, %es
	mov  %ax, %fs
	mov  %ax, %gs


// Совершаем дальний прыжок, что позволяет
// загрузить теневую часть сегментного регистра cs
// и перейти в 32-х битный код
	ljmp $0x08, $pmmain











.code32
//---------------------------------------------------protected mode--------------------------------------------------
pmmain:
// Устанавливаем указатель стека
	mov $0x9FFFF, %esp

// Включаем немаскируемые прерывания
	in $0x70, %al
	and $0x7F, %al
	out %al, $0x70

// Инициализация в защищенном режиме
	call init32

// Переход в код ядра
	jmp _osmain









/**
 * Глобальная таблица дескрипторов
 * Здесь объявлены только первые три
 * дескриптора. Перед переходом в PM
 * они будут скопированы по адресу 0xD00
 *
 * Структура дескриптора:
 * Байт 0,1:   Лимит
 * Байт 2,3,4: База [0-23]
 * Байт 5:     (0-Бит присутствия) (00-Нулевой уровень привилегий) (0-Дескриптор [обычный] кода или данных) (1010-Код для исполнения/чтения, 0010-Данные для чтения/записи)
 * Байт 6:     (0-Бит гранулярности) (0-32-х битный сегмент) (0-Должен быть ноль) (0-Не имеет значения, пользовательский) (0000-Лимит)
 * Байт 7:     База [24-31]
**/

gdt:
// Нулевой дескриптор. Обязателен
	.byte 0,0,0,0,0,0,0,0

// Дескриптор кода 4GB
	.word 0xFFFF
	.byte 0, 0, 0
	.byte 0b10011010
	.byte 0b11001111
	.byte 0

// Дескриптор данных 4GB
	.word 0xFFFF
	.byte 0, 0, 0
	.byte 0b10010010
	.byte 0b11001111
	.byte 0

gdtr:
.word GdtSize-1
.long GdtAddress










/**
 * Таблица дескрипторов прерываний
 * все дескрипторы будут сформированы
 * из кода ядра
 *
 * Поскольку сама таблица расположена
 * в адресах 0x500-0xCFF, здесь мы
 * размещаем только значение регистра IDTR
**/
idtr:
.word IdtSize-1
.long IdtAddress









loadingStartedMessage: .ascii "                              [OS Fenix (c) kernel]                             \0"

loadingFailedMessage:  .ascii "                             Fatal:  Loading Failed                             "
                       .ascii "                            Press any key for reboot                            \0"


/**
 * Директива .org используется для выравнивания
 * размеров загрузчика до 512 байт загрузочного
 * сектора. Затем следует сигнатура загрузчика,
 * 0xAA55. Она может требоваться BIOS.
**/

.org 510

signature:
.word 0xAA55
