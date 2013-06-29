CXX		= g++
GAS		= as
LINK		= ld
OBJCOPY		= objcopy
REMOVE		= erase /F
COPY		= copy /Y

CXXFLAGS	= -c --no-builtin -nostdlib
GASFLAGS	= 
LINKFLAGS	= -s -Ttext 0x100000

INCLUDES	= -I. -I..\include
TARGET		= bin\andromeda-core





all: $(TARGET)

$(TARGET): obj\boot.o obj\main.o
	$(LINK) $(LINKFLAGS) -o $@ $^
	$(OBJCOPY) $(TARGET) -O elf32-i386

obj\boot.o: boot.s
	$(GAS) $(GASFLAGS) $(INCLUDES) -o $@ $^

obj\main.o: main.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -o $@ $^

install: $(TARGET)
	$(COPY) $(TARGET) C:\$(TARGET)

clean:
	$(REMOVE) $(TARGET) obj\boot.o obj\main.o
