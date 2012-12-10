loop_init:
	pushfd

loop:
	mov eax, 0x00c0ffee

loop_end:
	jmp loop

popfd
