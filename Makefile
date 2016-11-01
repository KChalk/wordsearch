GCC = gcc

OBJS = ws1.o

all: WS

WS: $(OBJS)
	$(CC) -o  WS $(OBJS)  
.c.o:
	$(CC) $(CFLAGS) -std=gnu99 -g -Wall -Wextra -c $<
	
clean:
	rm -f WS *.o core
