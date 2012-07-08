; This is going to be tiny. :]

BITS 32
GLOBAL _start

SECTION .text
_start:
	xor eax, eax
	inc eax
	mov bl, 42
	int 0x80
