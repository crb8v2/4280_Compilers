CC = g++
CFLAGS = -g

TARGET1 = statSem
OBJS1 = main.o
OBJS2 = scanner.o
OBJS3 = parser.o
OBJS4 = printTree.o
OBJS5 = statSem.o
HEADER = node.h

all: $(TARGET1)

statSem: $(OBJS1) $(OBJS2) $(OBJS3) $(OBJS4) $(OBJS4)
	$(CC) $(CFLAGS) -o statSem main.o scanner.cpp parser.cpp printTree.cpp statSem.cpp

%.o: %.c  $(HEADER)
	g++ -c $(CFLAGS) $*.cpp -o $*.o

clean:
	/bin/rm -f *.o
	/bin/rm -f $(TARGET1)
	/bin/rm -f raw.input1
	/bin/rm -f toScanner.txt
	/bin/rm -f tokenIDs.txt