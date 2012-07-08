CC=gcc
CFLAGS=-g3 -Wall -Wextra -o
LDFLAGS=-lelf
OBJ=bin/main.o bin/log.o bin/crypt.o

all: bin/main

bin/%.o: src/%.c
	$(CC) $^ -c $(CFLAGS) $@

bin/main: $(OBJ)
	$(CC) $(LDFLAGS) $^ $(CFLAGS) $@

.PHONY: clean

clean:
	rm -f bin/*
