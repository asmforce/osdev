GAS		= as
CXX		= g++ -c
LINK		= ld
OBJCOPY		= objcopy -O binary
COPY		= copy /Y /B > nul
REMOVE		= erase /F
GASFLAGS	=
CXXFLAGS	= -nostdlib -fomit-frame-pointer -ffreestanding
LINKFLAGS	= -Ttext 0x0
INCLUDE		= -I "include" -I "..\include"
MBS		= bin\mbs.bin
RMS		= bin\rmsetup.bin
PMS		= bin\pmsetup.bin
TESTTRG		= e:\vmachine\disks\andromeda.vmdk

ETOOLS		= .\..\tools\bin
TRUNC		= truncate.exe -i
VMDKHEAD	= bin\vmdk-head



all: $(MBS) $(RMS) $(PMS)

$(MBS): obj\mbs.o
	$(LINK) $(LINKFLAGS) -o $@ $^
	$(OBJCOPY) $@
	$(ETOOLS)\$(TRUNC) -s 512 $@

$(RMS): obj\rmsetup.o
	$(LINK) $(LINKFLAGS) -o $@ $^
	$(OBJCOPY) $@
	$(ETOOLS)\$(TRUNC) -s 1024 $@

$(PMS): obj\pmsetup.o obj\setup.o obj\pic.o
	$(LINK) -Ttext 0x1900 -o $@ $^
	$(OBJCOPY) $@
	$(ETOOLS)\$(TRUNC) -s 31232 $@

obj\mbs.o: mbs.S
	$(GAS) $(INCLUDE) $(GASFLAGS) -o $@ $^

obj\rmsetup.o: rmsetup.S
	$(GAS) $(INCLUDE) $(GASFLAGS) -o $@ $^

obj\pmsetup.o: pmsetup.S
	$(GAS) $(INCLUDE) $(GASFLAGS) -o $@ $^

obj\setup.o: setup.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -o $@ $^

obj\pic.o: src\pic.cpp
	$(CXX) $(INCLUDE) $(CXXFLAGS) -o $@ $^

install: $(MBS) $(RMS) $(PMS)
# temporary available function :)
	$(COPY) $(VMDKHEAD)+$(MBS)+$(RMS)+$(PMS) $(TESTTRG)

clean:
	$(REMOVE) $(TESTTRG) $(MBS) $(RMS) $(PMS) obj\mbs.o obj\rmsetup.o obj\pmsetup.o obj\setup.o obj\pic.o
