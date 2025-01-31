ENTRY(Reset_Handler)


MEMORY
{
    FLASH(rx) : ORIGIN = 0x000E0000, LENGTH = 0x1E000
    RAM(rwx) :   ORIGIN = 0x20020000, LENGTH = 0x20000 
}

SECTIONS
{
    .text :
    {
        /* __my_test_start = .;
        KEEP(*(.APP_SECTION_HEADER))
        __my_test_end = .; */
        KEEP(*(.isr_vector))
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


