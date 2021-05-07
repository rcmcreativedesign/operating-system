C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

all: os-image

os-image: boot/boot.bin kernel.bin
	cat $^ > os-image
	
kernel.bin : kernel/kernel_entry.o ${OBJ}
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

%.o : %.c ${HEADERS}
	i686-elf-gcc -ffreestanding -c $< -o $@

%.o : %.asm
	nasm $< -f elf -o $@

%.bin: %.asm
	nasm $< -f bin -I boot/ -o $@
	
clean:
	rm -fr *.bin *.o os-image *.dis *.map
	rm -fr kernel/*o boot/*.bin drivers/*.o
	
kernel.dis: kernel.bin
	ndisasm -b 32 $< > $@