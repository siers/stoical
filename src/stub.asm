BITS 32

init:
	pusha							; push all gen. purp. registers
	mov ebx, 0xc0febabe				; .text addr
	xor eax, eax

loop:
	xor byte [ebx + eax], 216
	inc eax
	cmp eax, 0xcccccccc				; .text's len - stub's code
	jne loop

fin:
	popa
	mov eax, 0xeeeeeeee				; real e_entry addr
	jmp eax
