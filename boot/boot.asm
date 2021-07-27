[org 0x7c00]
KERNEL_OFFSET equ 0x1000
boot:
	jmp boot_main
	times 3-($-$$) DB 0x90

	OEMname: 			db	"mkfs.fat"
	bytesPerSector:		dw	512
	sectPerCluster:		db	1
	reservedSectors:	dw	1
	numFAT:				db	2
	numRootDirEntries:	dw	224
	numSectors:			dw	2880
	mediaType:			db	0xf0
	numFATsectors:		dw	9
	sectorsPerTrack:	dw	18
	numHeads:			dw	2
	numHiddenSectors:	dd	0
	numSectorsHuge:		dd	0
	driveNum:			db	0
	reserved:			db	0
	signature:			db	0x29
	volumeID:			dd	0x2d7e5a1a
	volumeLabel:		db	"NO NAME    "
	fileSysType:		db	"FAT12"
	
boot_main:
	mov [BOOT_DRIVE], dl
	
	mov bp, 0x9000
	mov sp, bp
	
    xor ax, ax
    mov ds, ax
    mov es, ax
    
	mov bx, MSG_REAL_MODE
	call print_string
	call print_new_line
	call load_kernel
	call switch_to_pm
	jmp $
	
%include "print_string_function.asm"
%include "print_hex_function.asm"
%include "read_disk.asm"
%include "gdt.asm"
%include "print_string_pm.asm"
%include "switch_to_pm.asm"

[bits 16]
load_kernel:
	mov bx, MSG_LOAD_KERNEL
	call print_string
	
	mov bx, KERNEL_OFFSET
	mov dh, 20
	mov dl, [BOOT_DRIVE]
	call disk_load
	
	ret
	
[bits 32]
BEGIN_PM:
	mov ebx, MSG_PROT_MODE
	call print_string_pm
	
	call KERNEL_OFFSET
	
	jmp $
	
BOOT_DRIVE db 0
MSG_REAL_MODE db "Started in 16-bit Real Mode",0
MSG_PROT_MODE db "Successfully landed in 32-bit Protected Mode",0
MSG_LOAD_KERNEL db "Loading kernel into memory.",0	
	
	times 510-($-$$) db 0
	dw 0xaa55
	
