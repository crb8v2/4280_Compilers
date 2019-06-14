CC = g++
CFLAGS = -std=c++11

TARGET1 = comp
OBJS1 = main.o
OBJS2 = scanner.o
OBJS3 = parser.o
OBJS4 = printTree.o
OBJS5 = statSem.o
OBJS6 = semantics.o
HEADER = node.h

all: $(TARGET1)

comp: $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS4) $(OBJS5) $(OBJS6)
	$(CC) $(CFLAGS) -o comp main.o scanner.cpp parser.cpp printTree.cpp statSem.cpp semantics.cpp

%.o: %.c  $(HEADER)
	g++ -c $(CFLAGS) $*.cpp -o $*.o

clean:
	/bin/rm -f *.o
	/bin/rm -f $(TARGET1)
	/bin/rm -f raw.input1
	/bin/rm -f toScanner.txt
	/bin/rm -f tokenIDs.txt
	/bin/rm -f test.asm