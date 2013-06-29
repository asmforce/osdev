CXX	= g++ -c
LINK	= g++ -s --static-libgcc
REMOVE	= erase /F
INCLUDE	= -I. -I.\..\include
LIBS	= -L.
TARGET	= pcp.exe





all: $(TARGET)

$(TARGET): main.o
	$(LINK) $(LIBS) -o $@ $^

main.o: main.cpp
	$(CXX) $(INCLUDE) -o $@ $^

clean:
	$(REMOVE) $(TARGET) main.o
