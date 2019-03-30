CC = g++
CFLAGS = -g

TARGET1 = scanner
OBJS1 = main.o
OBJS2 = scanner.o
OBJS3 = testScanner.o
HEADER = node.h


all: $(TARGET1)

scanner: $(OBJS1) $(OBJS2) $(OBJS3)
	$(CC) $(CFLAGS) -o scanner main.o testScanner.cpp scanner.cpp prefilter.cpp postfilter.cpp

%.o: %.c  $(HEADER)
	g++ -c $(CFLAGS) $*.cpp -o $*.o

clean:
	/bin/rm -f *.o
	/bin/rm -f $(TARGET1)
	/bin/rm -f raw.input1
	/bin/rm -f toScanner.txt