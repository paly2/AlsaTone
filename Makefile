CC=gcc
CFLAGS=-lm -lasound
EXEC=alsatone

all:
	$(CC) alsatone.c -o $(EXEC) $(CFLAGS)
