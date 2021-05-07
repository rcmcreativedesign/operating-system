all: os-image

os-image: boot_sect.bin kernel.bin
	cat $* > os-image
	
kernel.bin : kernel_entry.o kernel.o
	i686-elf-ld -o kernel.bin -Ttext 0x1000 $^ --oformat binary
	
kernel.o: kernel.c
	i686-elf-gcc -ffreestanding -c $< -o $@
	
kernel_entry.o: kernel_entry.asm
	nasm $< -f elf -o $@
	
boot_sect.bin: boot.asm
	nasm $< -f bin -o $@
	
clean:
	rm -fr *.bin *.o os-image *.dis *.map
	
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@