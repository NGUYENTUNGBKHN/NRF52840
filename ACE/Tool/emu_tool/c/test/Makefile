
# Biên dịch thành object file
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -g -nostdlib -nostartfiles -ffreestanding -c main.c -o main.o

# Liên kết với linker script và tạo ELF executable
arm-none-eabi-ld -T linker.ld main.o -o main.elf

# Tạo binary file (đây là file bạn sẽ tải vào trình mô phỏng của mình)
arm-none-eabi-objcopy -O binary main.elf program.bin