@echo off

if exist bin\xworkspace del bin\xworkspace


rem -----------------------------------
rem -----------------------------------
rem --------BOOT AND INITIALIZE--------
rem -----------------------------------
rem -----------------------------------

cd iniz
rem assembly
as -o bin\boot.o   src\boot.s
as -o bin\init16.o src\init16.s
as -o bin\init32.o src\init32.s

rem link
ld -Ttext 0x0 -o    bin\boot.bin   bin\boot.o
ld -Ttext 0x1600 -o bin\init16.bin bin\init16.o

rem convert
objcopy bin\boot.bin -O binary   bin\boot
objcopy bin\init16.bin -O binary bin\init16
cd ..



rem -----------------------------------
rem -----------------------------------
rem ---------------XCORE---------------
rem -----------------------------------
rem -----------------------------------

cd xcore
gcc -I include -c -o bin\iniz.o       src\iniz.c
gcc -I include -c -o bin\xmain.o      src\xmain.c
gcc -I include -c -o bin\task.o       src\task.c
as  -I include    -o bin\igates.o     src\igates.s
gcc -I include -c -o bin\string.o     src\string.c
gcc -I include -c -o bin\cmos.o       src\cmos.c
rem gcc -I include -c -o bin\tty.o        src\tty.c
gcc -I include -c -o bin\vconsole.o   src\vconsole.c
cd ..




rem -----------------------------------
rem -----------------------------------
rem ------------IMAGE BUILD------------
rem -----------------------------------
rem -----------------------------------

ld -Ttext 0x1E00 -o bin\xcore.bin  iniz\bin\init32.o xcore\bin\*.o
objcopy bin\xcore.bin -O binary bin\xcore

rem making image
.\cp.exe bin\xworkspace iniz\bin\boot 512 iniz\bin\init16 2048 bin\xcore 30208



rem if attempt isn't successful, - pause
if not exist bin\xworkspace @pause
