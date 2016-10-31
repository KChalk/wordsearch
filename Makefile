GCC = gcc

OBJS = ws1.o

all: WS

WS: $(OBJS)
	$(CC) -gnu99 -o  WS $(OBJS)  
.c.o:
	$(CC) $(CFLAGS) -g -Wall -c $<
	
clean:
	rm -f WS *.o core
