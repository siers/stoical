AC=yasm
CC=gcc
AFLAGS=-f elf -o
CFLAGS=-nostdlib -nostartfiles -s -o

all: smaller main

%.o: %.s
	$(AC) $^ $(AFLAGS) $@

smaller: smaller.asm
	$(AC) $^ $(AFLAGS) $@ -f bin
	chmod +x $@

main: asm.o
	$(CC) $^ $(CFLAGS) $@
	objcopy main --remove-section=.{note.gnu.build-id,strtab} main

.PHONY: clean

clean:
	rm -f *.o main smaller
