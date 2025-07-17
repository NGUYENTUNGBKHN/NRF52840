/* linker.ld */
ENTRY(main)

/* Định nghĩa vùng nhớ (Memory Region) - quan trọng cho linker */
/* Thường được định nghĩa trong một file riêng hoặc ở đầu linker.ld */
MEMORY
{
  RAM_ALIAS (rwx) : ORIGIN = 0x0, LENGTH = 512K /* Địa chỉ và kích thước RAM */
}


SECTIONS
{
  . = 0x0; /* Chương trình sẽ được tải và chạy từ địa chỉ 0x0 trong RAM mô phỏng */
  .text : {
    KEEP(*(.vectors)) /* Giữ vector table nếu có */
    *(.text)
    *(.rodata)
  } >RAM_ALIAS /* RAM_ALIAS là tên vùng nhớ trong script lớn hơn, ở đây ta giả định là RAM_ALIAS */

  .data : {
    *(.data)
  } >RAM_ALIAS

  .bss : {
    *(.bss)
  } >RAM_ALIAS

  _end = .; /* Kết thúc chương trình */
}

