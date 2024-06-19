
SEARCH_DIR(.)
GROUP(-lgcc -lc -lnosys)

ENTRY(Reset_Handler)

MEMORY
{
    FLASH(rx) : ORIGIN = 0x0000000, LENGTH = 0x100000
    RAM (rww) : ORIGIN = 0x20000000, LENGTH = 0x40000
}

SECTIONS
{
    .text :
    {
        KEEP(*(.isr_vector))
        *(.text)
        *(.text.*)
        *(.rodata)
    } > FLASH

    .data : 
    {
        *(.data)
        *(.data.*)
    } > RAM

    .bss : 
    {
        *(.bss)
    } > RAM

    _estack = ORIGIN(RAM) + LENGTH(RAM);
}


