CC = gcc
CFLAGS = -Wall -Wextra -g

all: membox

membox: main.o membox.o util.o
	$(CC) $(CFLAGS) -o membox main.o membox.o util.o

main.o: main.c membox.h
	$(CC) $(CFLAGS) -c main.c

membox.o: membox.c membox.h util.h
	$(CC) $(CFLAGS) -c membox.c

util.o: util.c util.h
	$(CC) $(CFLAGS) -c util.c

clean:
	rm -f *.o membox
