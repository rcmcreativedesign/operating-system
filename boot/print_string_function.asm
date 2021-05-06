print_string:
	pusha
	
	mov ah, 0x0e

start_loop:
	mov al, [bx]
	cmp al, 0
	je done
	
	int 0x10
	
	add bx, 1
	jmp start_loop
	
done:
	popa
	ret

print_new_line:
	pusha
	
	mov ax, 0x0e0a
	int 0x10
	mov al, 0x0d
	int 0x10
	
	popa
	ret