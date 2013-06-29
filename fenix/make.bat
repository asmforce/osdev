@echo off
if exist bin\fenix del bin\fenix

c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/boot.o boot/boot.s
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/init32.o boot/init32.s
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/osmain.o osmain.c

c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/console.o core/console.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/string.o core/string.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/cmos.o core/cmos.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/clock.o core/clock.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/memory.o core/memory.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/systables.o core/systables.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/task.o core/task.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/ide.o core/ide.c
c:\programs\mingw\bin\gcc -ffreestanding -c -o bin/syscall.o core/syscall.s

c:\programs\mingw\bin\ld -Ttext 0x7C00 -o bin/fenix.bin bin/boot.o bin/init32.o bin/task.o bin/syscall.o bin/osmain.o bin/ide.o bin/systables.o bin/memory.o bin/string.o bin/cmos.o bin/clock.o bin/console.o

c:\programs\mingw\bin\objcopy bin/fenix.bin -O binary
partcopy bin/fenix.bin 0 4000 bin/fenix

if not exist bin/fenix @pause