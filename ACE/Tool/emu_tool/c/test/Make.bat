
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -g -nostdlib -nostartfiles -ffreestanding -c main.c -o main.o

arm-none-eabi-ld -T linker.ld main.o -o main.elf

arm-none-eabi-objcopy -O binary main.elf program.bin
