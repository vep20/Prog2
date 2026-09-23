CC = gcc

foo: main.o greeter.o
	$(CC) -o foo main.o greeter.o

main.o: main.c
	$(CC) -c -Wall -Wextra -Werror -o main.o main.c

greeter.o: greeter.c
	$(CC) -c -Wall -Wextra -Werror -o greeter.o greeter.c
