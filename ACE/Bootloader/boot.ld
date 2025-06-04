/**
    * @file boot.ld
    * @brief Linker script for the bootloader.
    * @version 0.1
    * @date 2023-10-01
    **/

ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

_Min_Heap_Size = 0x200; /* required amount of heap */
_Min_Stack_Size = 0x400; /* required amount of stack */

MEMORY
{
    FLASH(rx) : ORIGIN = 0x00, LENGTH = 0x9FFFF
    FLASH_TRACE(rx) : ORIGIN = 0xA0000, LENGTH = 0x3FFFF
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 
}

SECTIONS
{
    /* ==== FLASH ===*/
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } >FLASH

    .text :
    {
        . = ALIGN(4);
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        *(.glue_7)         /* glue arm to thumb code */
        *(.glue_7t)        /* glue thumb to arm code */
        *(.eh_frame)

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
        _etext = .;        /* define a global symbols at end of code */
    } >FLASH

    /* Constant data into "FLASH" Rom type memory */
    .rodata :
    {
        . = ALIGN(4);
        *(.rodata)         /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
        . = ALIGN(4);
    } >FLASH

    /* _sidata = .; */
    _sidata = LOADADDR(.data); /* load address of .data section */

    /* _ramfunc_load_start = LOADADDR(.ram_code); load address of .text section */


    /* ==== RAM ===*/
    .data : /*AT(_sidata)*/
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT>FLASH

    .bss :
    {
        . = ALIGN(4);
        _sbss = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        _ebss = .;
    } >RAM

    .ram_code :
    {
        _ramcode_load_start = LOADADDR(.ram_code);
        . = ALIGN(4);
        _sram_code = .;
        *(.ram_code)
        *(.ram_code.*)
        . = ALIGN(4);
        _eram_code = .;
    } > RAM AT> FLASH_TRACE
    /* Remove information from the compiler libraries */

    ._user_heap_stack :
    {
        . = ALIGN(8);
        PROVIDE ( end = . );
        PROVIDE ( _end = . );
        . = . + _Min_Heap_Size;
        . = . + _Min_Stack_Size;
        . = ALIGN(8);
    } >RAM
    /DISCARD/ :
    {
        /* libc.a ( * )
        libm.a ( * )
        libgcc.a ( * ) */
    }
}


