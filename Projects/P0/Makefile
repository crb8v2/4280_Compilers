CC = g++
CFLAGS = -g

TARGET1 = P0
OBJS1 = main.o
OBJS2 = tree.o
HEADER = node.h


all: $(TARGET1)

P0: $(OBJS1) $(OBJS2)
	$(CC) $(CFLAGS) -o P0 main.o tree.cpp

%.o: %.c  $(HEADER)
	g++ -c $(CFLAGS) $*.cpp -o $*.o

clean:
	/bin/rm -f *.o
	/bin/rm -f $(TARGET1)
	/bin/rm -f *.dat
