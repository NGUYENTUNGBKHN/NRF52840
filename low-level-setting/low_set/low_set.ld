
ENTRY(Reset_Handler)


MEMORY
{
    FLASH(rx) : ORIGIN = 0x00, LENGTH = 0xE0000
    RAM (rwx) : ORIGIN = 0x20000000, LENGTH = 0x20000 
}

SECTIONS
{
    .text :
    {
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


