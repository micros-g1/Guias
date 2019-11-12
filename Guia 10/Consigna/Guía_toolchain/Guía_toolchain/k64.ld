MEMORY                                                          
{
    flash (rx) :	ORIGIN = 0x00000000, LENGTH = 1024k
    ram (rwx) : 	ORIGIN = 0x20000000, LENGTH = 192K
}

ENTRY(_reset_vector)

SECTIONS
{
    .vectors :
	{
		*(.vectors*)
	} > flash

    .text : ALIGN(2)
    {
        . = ALIGN(4);
        *(.text*)
        *(.rodata*)
    } > flash

    .data :
    {
        . = ALIGN(4);
        _data_start = .;
        *(.data*)
        . = ALIGN(4);
        _data_end = .;
    } > ram AT > flash
	
    _data_init_values = LOADADDR(.data);

    .bss (NOLOAD) :
    {
        . = ALIGN(4);
        _bss_start = . ;
        *(.bss*)
        *(COMMON)
        . = ALIGN(4);
        _bss_end = . ;
    } > ram

    _sp_init_value = ORIGIN(ram) + LENGTH(ram);
} 