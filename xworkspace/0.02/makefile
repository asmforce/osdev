#
# @author: Vitaliy Krutko
# @e-mail: asmforce@ukr.net asmxforce@gmail.com
# @project: os xworkspace
# @target: image
#

CC		=	gcc -c
LINK		=	ld
OBJCOPY		=	objcopy
MAKE		=	make
PARTCOPY	=	.\cp.exe
REMOVE		=	erase /F
TARGET		=	bin\xworkspace.bin
VBOXMANAGE	=	"C:\Program Files\VirtualBox\VBoxManage.exe"


all: $(TARGET)
	$(VBOXMANAGE) convertfromraw bin\xworkspace.bin bin\xworkspace.vdi
	copy /Y bin\xworkspace.vdi e:\vmachine\disks

$(TARGET): bin\boot.bin bin\iniz16.bin bin\core.bin
	$(PARTCOPY) $@ bin\boot.bin 512 bin\iniz16.bin 2048 bin\core.bin 30208

bin\boot.bin:
	$(MAKE) -f makefile.iniz all

bin\iniz16.bin:
	$(MAKE) -f makefile.iniz all

bin\core.bin:
	$(MAKE) -f makefile.core all

clean:
	$(REMOVE) $(TARGET) bin\boot.bin bin\iniz16.bin bin\core.bin
	$(MAKE) -f makefile.core clean
	$(MAKE) -f makefile.iniz clean
	$(REMOVE) bin\xworkspace.vdi
