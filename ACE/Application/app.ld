
ENTRY(Reset_Handler)

_estack = ORIGIN(RAM) + LENGTH(RAM);

MEMORY
{
    FLASH_TRACE(rx) : ORIGIN = 0x10000, LENGTH = 0x0FFFF
    FLASH(rx) : ORIGIN = 0x00020000, LENGTH = 0x1E000
    RAM (rwx) : ORIGIN = 0x20020000, LENGTH = 0x20000 
}

SECTIONS
{
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

    /* _sidata = LOADADDR(.data); */
    _sidata = LOADADDR(.data); /* load address of .data section */

    .data : 
    {
        . = ALIGN(4);
        _sdata = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        _edata = .;
    } >RAM AT >FLASH

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
    /DISCARD/ :
    {
        /* libc.a ( * )
        libm.a ( * )
        libgcc.a ( * ) */
    }

}


