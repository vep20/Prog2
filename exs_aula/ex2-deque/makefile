# Makefile de exemplo (Manual do GNU Make)
     
CFLAGS = -Wall -Wextra -g -std=c99 # flags de compilacao
CC = gcc

all: verifica_palindromo.o deque.o
	$(CC) -o verifica_palindromo verifica_palindromo.o deque.o

deque.o: deque.c deque.h
	$(CC) -c $(CFLAGS) deque.c

verifica_palindromo.o: verifica_palindromo.c deque.h
	$(CC) -c $(CFLAGS) verifica_palindromo.c

clean:
	rm -f *.o *~ verifica_palindromo