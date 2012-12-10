CC=gcc
CFLAGS=-g3 -Wall -Wextra -D_GNU_SOURCE -o
LDFLAGS=-lelf
OBJ=bin/main.o bin/log.o bin/crypt.o

AC=nasm
AFLAGS=-f bin -o

all: bin/stub.bin.tmpl main

bin/%.bin.tmpl: src/%.asm
	$(AC) $^ $(AFLAGS) $@

main: $(OBJ)
	$(CC) $(LDFLAGS) $^ $(CFLAGS) $@

bin/%.o: src/%.c
	$(CC) $^ -c $(CFLAGS) $@

.PHONY: clean

clean:
	rm -f bin/*
