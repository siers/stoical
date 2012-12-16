BITS 32

init:
	pusha							; push all gen. purp. registers
	mov ebx, 0xc0febabe				; .text addr
	xor eax, eax					; init the counter

loop:
	xor byte [ebx + eax], 216
	inc eax
	cmp eax, 0xcccccccc					; 0xcccc = .text's len - stub's code
	jne loop

fin:
	popa
	mov eax, 0xc0febabe					; .text addr
	push eax
	ret
	;jmp far [0x23:0xc0febabe]					; .text addr
