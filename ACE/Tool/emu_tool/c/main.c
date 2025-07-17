/******************************************************************************/
/*! @addtogroup Group2s
    @file       main.c
    @brief      
    @date       2025/07/14
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Define structure of ARMv7M ---
typedef struct {
    uint32_t r[13]; // R0-R12
    uint32_t sp;    // R13 (Stack Pointer)
    uint32_t lr;    // R14 (Link Register)
    uint32_t pc;    // R15 (Program Counter)
    uint32_t psr;   // Program Status Register (APSR, IPSR, EPSR)
} ARMv7M_CPU_State;

// --- Define Memory ---
#define RAM_SIZE (1 * 1024) // 512KB RAM 
uint8_t *ram;

#define UART0_BASE_ADDR     0x40000000 // UART
#define UART0_DR_OFFSET     0x00       // Data Register Offset
#define UART0_SR_OFFSET     0x04       // Status Register Offset (để kiểm tra sẵn sàng)

// Function read memory simulator
uint32_t mem_read32(uint32_t addr) {
    // Determine address in RAM
    if (addr >= 0 && addr < RAM_SIZE) {
        return *(uint32_t *)(ram + addr);
    }
    
    else if (addr >= UART0_BASE_ADDR && addr < (UART0_BASE_ADDR + 0x1000)) {
        
        if (addr == (UART0_BASE_ADDR + UART0_SR_OFFSET)) {
            return 0xFFFFFFFF;
        }
        // Other uart register.
    }
    printf("ERROR: Attempted to read from invalid memory address: 0x%X\n", addr);
    exit(1);
}

// Function write memory simulator
void mem_write32(uint32_t addr, uint32_t data) {
    // Determine address in RAM
    if (addr >= 0 && addr < RAM_SIZE) {
        *(uint32_t *)(ram + addr) = data;
    }
    else if (addr >= UART0_BASE_ADDR && addr < (UART0_BASE_ADDR + 0x1000)) {
        if (addr == (UART0_BASE_ADDR + UART0_DR_OFFSET)) {
            printf("%c", (char)data);
            fflush(stdout);
        }
    }
    else {
        printf("ERROR: Attempted to write to invalid memory address: 0x%X with data 0x%X\n", addr, data);
        exit(1);
    }
}

// --- Function load program ---
void load_program(const char *filename, uint32_t load_address) {
    FILE *f = fopen(filename, "rb");
    if (!f) {
        perror("Could not open program file");
        exit(1);
    }
    fseek(f, 0, SEEK_END);
    long fsize = ftell(f);
    fseek(f, 0, SEEK_SET);

    if ((load_address + fsize) > RAM_SIZE) {
        printf("ERROR: Program too large for RAM.\n");
        exit(1);
    }

    fread(ram + load_address, fsize, 1, f);
    fclose(f);
    printf("Program '%s' loaded successfully to 0x%X, size %ld bytes.\n", filename, load_address, fsize);
}

// --- Function encode program and execute instruction ---
void emulate_instruction(ARMv7M_CPU_State *cpu) {
    // Lấy lệnh từ bộ nhớ tại PC
    uint32_t instruction = mem_read32(cpu->pc);

    // Cortex-M4 hỗ trợ tập lệnh Thumb-2. Các lệnh có thể là 16-bit hoặc 32-bit.
    // Để đơn giản ban đầu, chúng ta có thể giả định tất cả là 32-bit
    // (hoặc bắt đầu với chỉ các lệnh 16-bit nếu bạn muốn đơn giản hơn nữa).
    // Tuy nhiên, việc nhận diện lệnh 16-bit hay 32-bit là bước quan trọng.
    // Lấy 2 bit đầu tiên của byte cao nhất để xác định độ dài lệnh:
    // 0b11101, 0b11110, 0b11111 là bắt đầu của lệnh Thumb 32-bit.
    // Các tiền tố khác là lệnh Thumb 16-bit.

    // Để đơn giản hóa ban đầu, chúng ta sẽ chỉ giải mã một vài lệnh ví dụ
    // và giả định PC luôn tăng 4 (cho lệnh 32-bit).

    // Tăng PC lên trước khi thực thi lệnh hiện tại
    // (hoạt động của PC trong ARMv7-M có thể phức tạp hơn một chút với pipeline)
    cpu->pc += 4;

    // --- Các ví dụ về giải mã và thực thi lệnh ---
    // (Đây là phần phức tạp nhất và yêu cầu đọc tài liệu ARMv7-M)

    // Ví dụ: Lệnh BL (Branch with Link)
    // Một lệnh BL sẽ nhảy đến một địa chỉ mới và lưu địa chỉ trả về vào LR (R14)
    // Cần phải phân tích opcode và offset từ instruction
    // if (is_bl_instruction(instruction)) {
    //     int32_t offset = decode_bl_offset(instruction);
    //     cpu->lr = cpu->pc; // LR = địa chỉ lệnh tiếp theo
    //     cpu->pc += offset; // Nhảy đến địa chỉ đích
    // }

    // Ví dụ: LDR (Load Register)
    // LDR R0, [R1, #offset]
    // if (is_ldr_instruction(instruction)) {
    //     uint8_t rd, rn;
    //     int32_t offset;
    //     decode_ldr_params(instruction, &rd, &rn, &offset);
    //     cpu->r[rd] = mem_read32(cpu->r[rn] + offset);
    // }

    // Ví dụ: STR (Store Register)
    // STR R0, [R1, #offset]
    // if (is_str_instruction(instruction)) {
    //     uint8_t rd, rn;
    //     int32_t offset;
    //     decode_str_params(instruction, &rd, &rn, &offset);
    //     mem_write32(cpu->r[rn] + offset, cpu->r[rd]);
    // }

    // Ví dụ: ADD (Add)
    // ADD R0, R1, R2
    // if (is_add_instruction(instruction)) {
    //     uint8_t rd, rn, rm;
    //     decode_add_params(instruction, &rd, &rn, &rm);
    //     cpu->r[rd] = cpu->r[rn] + cpu->r[rm];
    // }
    // --- Kết thúc phần giải mã và thực thi lệnh ---

    // Để đơn giản cho lần chạy đầu tiên, bạn có thể chỉ print ra lệnh và thoát
    // hoặc xử lý một vài lệnh hardcode để kiểm tra.
    printf("Executing instruction at 0x%X: 0x%08X\n", cpu->pc - 4, instruction); // In lệnh đã đọc
    // Nếu bạn không xử lý lệnh, vòng lặp sẽ trở thành vô hạn hoặc lỗi.
    // Để tránh lỗi ngay lập tức, bạn có thể thêm một điều kiện thoát.
    // Tuy nhiên, mục tiêu là mô phỏng từng lệnh.
}

// --- Main ---
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <program.bin>\n", argv[0]);
        return 1;
    }

    // Khởi tạo trạng thái CPU và bộ nhớ
    ARMv7M_CPU_State cpu_state;
    ram = (uint8_t *)malloc(RAM_SIZE);
    if (!ram) {
        perror("Failed to allocate RAM");
        return 1;
    }
    memset(ram, 0, RAM_SIZE);
    memset(&cpu_state, 0, sizeof(ARMv7M_CPU_State));

    // Cortex-M processors khởi động từ 0x0 hoặc địa chỉ trong vector table
    // Nạp chương trình vào đầu bộ nhớ RAM
    load_program(argv[1], 0x0);

    // Thiết lập PC ban đầu (điều này cũng phụ thuộc vào vector table/bootloader thực tế)
    // Đối với bare-metal đơn giản, chúng ta có thể đặt PC là địa chỉ tải
    cpu_state.pc = 0x0;
    // SP thường được khởi tạo từ giá trị đầu tiên trong vector table
    // cpu_state.sp = mem_read32(0x0); // Lấy giá trị SP từ vector table
    // cpu_state.pc = mem_read32(0x4) & ~1; // Lấy giá trị PC từ vector table, bit 0 phải là 1 cho Thumb mode

    printf("Starting emulation...\n");

    // Vòng lặp mô phỏng chính
    while (1) {
        // Kiểm tra điều kiện thoát (ví dụ: PC đi ra ngoài vùng chương trình hợp lệ)
        if (cpu_state.pc >= RAM_SIZE) { // Hoặc vượt quá kích thước chương trình đã tải
            printf("Program Counter out of bounds (0x%X). Exiting emulation.\n", cpu_state.pc);
            break;
        }

        // Gọi hàm thực thi một lệnh
        emulate_instruction(&cpu_state);

        // In trạng thái thanh ghi (để gỡ lỗi)
        // for (int i = 0; i < 13; ++i) {
        //     printf("R%d: 0x%08X ", i, cpu_state.r[i]);
        // }
        // printf("SP: 0x%08X LR: 0x%08X PC: 0x%08X\n", cpu_state.sp, cpu_state.lr, cpu_state.pc);
        // getchar(); // Giữ để xem từng bước nếu muốn
    }

    free(ram);
    return 0;
}

