C_SOURCES = $(wildcard kernel/*.c drivers/*.c drivers/disk/*.c libc/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h drivers/disk/*.h libc/*.h)
OBJ = ${C_SOURCES:.c=.o}

all: os-image

os-image: boot/boot.bin kernel.bin
	cat $^ > os-image
	
kernel.bin : boot/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o : %.c ${HEADERS}
	i686-elf-gcc -ffreestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -I boot/ -o $@
	
clean:
	rm -fr *.bin *.o os-image *.dis *.map
	rm -fr kernel/*o boot/*.bin boot/*.o drivers/*.o drivers/disk/*.o libc/*.o
	
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@