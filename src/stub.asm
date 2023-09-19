BITS 64

init:
	pusha							; push all gen. purp. registers
	mov rbx, 0xc0febabec0febabe		; placeholder for .text's addr
	xor rax, rax

loop:
	xor byte [rbx + rax], 216
	inc rax
	cmp rax, 0xc0fec0fec0fec0fe		; .text's len - stub's code
	jne loop

fin:
	popa
	mov rax, 0xbabebabebabebabe				; placeholder for real e_entry's addr
	jmp rax
