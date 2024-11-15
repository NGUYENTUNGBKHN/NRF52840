This material only guide to write a simple makefile

TARGET is name of output file 
BUILD_DIR is direction of build folder
OBJS_DIR is direction of objects file folder

- Toolchain
    + Toolchain used in project is arm-none-eabi-gcc.
    + 

- C flag -> you can refer "gnu compiler collection"
    + CPU : -mcpu=cortex-m4 => CPU declared cortex chip
    + FPU : -mfpu=fpv4-sp-d16
        **** floating point unit is a part of system computer, it carry out operation on floating-point numbers
    + OPT : optimization 
    + -Wall : Warning all
    + -Werror :  
    + -ffunction-section : 
    + fdata-section :
    + -fno-strict-aliasing : 

- ASM flag 
    + only declared CPU and FPU, OPT
- LIBS -> this library 
    + -lc -lm -lnosys

- Souce file 
    + use command "wildcard"  to search all file .c in ./ direction folder
    + 