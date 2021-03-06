[bits 32]
[extern main]

[global irq0]
[global irq1]
[global irq2]
[global irq3]
[global irq4]
[global irq5]
[global irq6]
[global irq7]
[global irq8]
[global irq9]
[global irq10]
[global irq11]
[global irq12]
[global irq13]
[global irq14]
[global irq15]
[global load_idt]

[extern irq0_handler]
[extern irq1_handler]
[extern irq2_handler]
[extern irq3_handler]
[extern irq4_handler]
[extern irq5_handler]
[extern irq6_handler]
[extern irq7_handler]
[extern irq8_handler]
[extern irq9_handler]
[extern irq10_handler]
[extern irq11_handler]
[extern irq12_handler]
[extern irq13_handler]
[extern irq14_handler]
[extern irq15_handler]

[global irq0_handler]
[global irq1_handler]
[global irq2_handler]
[global irq3_handler]
[global irq4_handler]
[global irq5_handler]
[global irq6_handler]
[global irq7_handler]
[global irq8_handler]
[global irq9_handler]
[global irq10_handler]
[global irq11_handler]
[global irq12_handler]
[global irq13_handler]
[global irq14_handler]
[global irq15_handler]

call main
jmp $

load_idt:
	mov edx, [esp + 4]
	lidt [edx]
	sti
	ret

irq0:
	pusha
	call irq0_handler
	popa
	iretd

irq1:
	pusha
	call irq1_handler
	popa
	iretd
	
irq2:
	pusha
	call irq2_handler
	popa
	iretd
	
irq3:
	pusha
	call irq3_handler
	popa
	iretd
	
irq4:
	pusha
	call irq4_handler
	popa
	iretd
	
irq5:
	pusha
	call irq5_handler
	popa
	iretd
	
irq6:
	pusha
	call irq6_handler
	popa
	iretd
	
irq7:
	pusha
	call irq7_handler
	popa
	iretd
	
irq8:
	pusha
	call irq8_handler
	popa
	iretd
	
irq9:
	pusha
	call irq9_handler
	popa
	iretd
	
irq10:
	pusha
	call irq10_handler
	popa
	iretd
	
irq11:
	pusha
	call irq11_handler
	popa
	iretd
	
irq12:
	pusha
	call irq12_handler
	popa
	iretd
	
irq13:
	pusha
	call irq13_handler
	popa
	iretd
	
irq14:
	pusha
	call irq14_handler
	popa
	iretd
	
irq15:
	pusha
	call irq15_handler
	popa
	iretd
	
	