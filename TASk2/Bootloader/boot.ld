
ENTRY(Reset_Handler)


MEMORY
{
    FLASH(rx) : ORIGIN = 0x00, LENGTH = 0xE0000
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 
}

SECTIONS
{
    /* .myTest :
    {
        __my_test_start = .;
        KEEP(*(.BOOT_SECTION_HEADER))
        __my_test_end = .;
    } >FLASH */

    .text :
    {
        KEEP(*(.isr_vector))
        __my_test_start = .;
        KEEP(*(.BOOT_SECTION_HEADER))
        __my_test_end = .;
        *(.text)
        *(.text.*)
        *(.rodata)
        _sidata = .;
    } >FLASH

    .data : AT(_sidata)
    {
        _sdata = .;
        *(.data)
        *(.data.*)
        _edata = .;
    } >RAM

    .bss :
    {
        _sbss = .;
        *(.bss)
        *(.bss.*)
        _ebss = .;
    } >RAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}


