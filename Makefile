CC=gcc
CFLAGS=-Wall
OBJS=main.o cipher.o

file_encryptor: $(OBJS)
	$(CC) -o file_encryptor $(OBJS)

main.o: main.c cipher.h
	$(CC) $(CFLAGS) -c main.c

cipher.o: cipher.c cipher.h
	$(CC) $(CFLAGS) -c cipher.c

clean:
	rm -f *.o file_encryptor
