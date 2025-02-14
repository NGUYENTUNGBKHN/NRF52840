/* Entry Point */
ENTRY(Reset_Handler)

/* Specify the memory areas */

MEMORY
{
    FLASH (rx)  : ORIGIN = 0x00000000, LENGTH = 0xE0000 /**/
    RAM (rwx)   : ORIGIN = 0x20000000, LENGTH = 0x20000
}

SECTIONS
{
    .isr_vector :
    {
        . = ALIGN(4);
        KEEP(*(.isr_vector))
        . = ALIGN(4);
    } > FLASH


    .custom_ram_block 0x20000100(NOLOAD) :
    {
        KEEP(*(.custom_ram_block))
    } > RAM

    .custom_flash_block 0x08010000 :
    {
        KEEP(*(.custom_flash_block))
    } > FLASH

    .text :
    {
        . = ALIGN(4);
        _stext = .;
        *(.text)           /* .text sections (code) */
        *(.text*)          /* .text* sections (code) */
        *(.rodata)         /* .rodata sections (constants, strings, etc.) */
        *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
        *(.glue_7)         /* glue arm to thumb code */
        *(.glue_7t)        /* glue thumb to arm code */
        *(.eh_frame)

        KEEP (*(.init))
        KEEP (*(.fini))

        . = ALIGN(4);
        _etext = .;
    } > FLASH
    
}

