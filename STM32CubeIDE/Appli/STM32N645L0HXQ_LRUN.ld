/*
******************************************************************************
**
** @file        : STM32N657XX_LRUN.ld
**
** @author      : GPM Application Team
**
** @brief       : Linker script for STM32N657XX Device from STM32N6 series
**                      2048 KBytes RAM
**
**                Set heap size, stack size and stack location according
**                to application requirements.
**
**                Set memory bank area and size if external memory is used
**
**  Target      : STMicroelectronics STM32
**
**  Distribution: The file is distributed as is, without any warranty
**                of any kind.
**
******************************************************************************
** @attention
**
** Copyright (c) 2023 STMicroelectronics.
** All rights reserved.
**
** This software is licensed under terms that can be found in the LICENSE file
** in the root directory of this software component.
** If no LICENSE file comes with this software, it is provided AS-IS.
**
******************************************************************************
*/

/* Entry Point */
ENTRY(Reset_Handler)


/* Memories definition */
MEMORY
{
  SRAM (xrw) : ORIGIN = 0x34000000, LENGTH = 0x00200000 /* 2MB Internal SRAM */
}
/* Highest address of the user mode stack */
_estack = ORIGIN(SRAM) + LENGTH(SRAM); /* end of SRAM */
_sstack = _estack - _Min_Stack_Size;

_Min_Heap_Size = 0x200;      /* required amount of heap  */
_Min_Stack_Size = 0x800; /* required amount of stack */

/* Link ISR vectors */
SECTIONS
{
  /* The startup code into SRAM */
  .isr_vector :
  {
    . = ALIGN(4);
    KEEP(*(.isr_vector)) /* Startup code */
    . = ALIGN(4);
  } >SRAM
}

/* Define specific placement of memory areas */
SECTIONS
{
  BufferSection (NOLOAD) :
  {
    *(TouchGFX_Framebuffer TouchGFX_Framebuffer.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x8);

    *(Nemagfx_Stencil_Buffer Nemagfx_Stencil_Buffer.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x8);
  } >SRAM
  
  UncachedSection (NOLOAD) :
  {
    *(Nemagfx_Memory_Pool_Buffer Nemagfx_Memory_Pool_Buffer.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x8);
  } >SRAM
  
  FontFlashSection :
  {
    *(FontFlashSection FontFlashSection.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x4);
  } >SRAM

  TextFlashSection :
  {
    *(TextFlashSection TextFlashSection.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x4);
  } >SRAM

  ExtFlashSection :
  {
    *(ExtFlashSection ExtFlashSection.*)
    *(.gnu.linkonce.r.*)
    . = ALIGN(0x4);
  } >SRAM
}

/* Sections */
SECTIONS
{
  /* The program code and other data into SRAM */
  .text :
  {
    . = ALIGN(4);
    *(.text)           /* .text sections (code) */
    *(.text*)          /* .text* sections (code) */
    *(.glue_7)         /* glue arm to thumb code */
    *(.glue_7t)        /* glue thumb to arm code */
    *(.eh_frame)
    *(.RamFunc)        /* .RamFunc sections */
    *(.RamFunc*)       /* .RamFunc* sections */

    KEEP (*(.init))
    KEEP (*(.fini))

    . = ALIGN(4);
    _etext = .;        /* define a global symbols at end of code */
  } >SRAM

  /* Constant data into SRAM */
  .rodata :
  {
    . = ALIGN(4);
    *(.rodata)         /* .rodata sections (constants, strings, etc.) */
    *(.rodata*)        /* .rodata* sections (constants, strings, etc.) */
    . = ALIGN(4);
  } >SRAM

  .ARM.extab   : {
    . = ALIGN(4);
    *(.ARM.extab* .gnu.linkonce.armextab.*)
    . = ALIGN(4);
  } >SRAM

  .ARM : {
    . = ALIGN(4);
    __exidx_start = .;
    *(.ARM.exidx*)
    __exidx_end = .;
    . = ALIGN(4);
  } >SRAM

  .preinit_array     :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__preinit_array_start = .);
    KEEP (*(.preinit_array*))
    PROVIDE_HIDDEN (__preinit_array_end = .);
    . = ALIGN(4);
  } >SRAM

  .init_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__init_array_start = .);
    KEEP (*(SORT(.init_array.*)))
    KEEP (*(.init_array*))
    PROVIDE_HIDDEN (__init_array_end = .);
    . = ALIGN(4);
  } >SRAM

  .fini_array :
  {
    . = ALIGN(4);
    PROVIDE_HIDDEN (__fini_array_start = .);
    KEEP (*(SORT(.fini_array.*)))
    KEEP (*(.fini_array*))
    PROVIDE_HIDDEN (__fini_array_end = .);
    . = ALIGN(4);
  } >SRAM

  /* Used by the startup to initialize data */
  .gnu.sgstubs ALIGN(32) :
  {
    _sNSCVeneer = .;
    *(.gnu.sgstubs*)   /* Secure Gateway stubs */
    . = ALIGN(32);
    FILL(0x00);
  } >SRAM
  _eNSCVeneer = .;

  /* Uninitialized data section into SRAM */
  _sidata = LOADADDR(.data);

  /* Initialized data sections into SRAM */
  .data :
  {
    . = ALIGN(4);
    _sdata = .;        /* create a global symbol at data start */
    *(.data)           /* .data sections */
    *(.data*)          /* .data* sections */

    . = ALIGN(4);

  } >SRAM

  /* Initialized TLS data section */
  .tdata : ALIGN(4)
  {
    *(.tdata .tdata.* .gnu.linkonce.td.*)
    . = ALIGN(4);
    _edata = .;        /* define a global symbol at data end */
    PROVIDE(__data_end = .);
    PROVIDE(__tdata_end = .);
  } >SRAM

  PROVIDE( __tdata_start = ADDR(.tdata) );
  PROVIDE( __tdata_size = __tdata_end - __tdata_start );

  PROVIDE( __data_start = ADDR(.data) );
  PROVIDE( __data_size = __data_end - __data_start );

  PROVIDE( __tdata_source = LOADADDR(.tdata) );
  PROVIDE( __tdata_source_end = LOADADDR(.tdata) + SIZEOF(.tdata) );
  PROVIDE( __tdata_source_size = __tdata_source_end - __tdata_source );

  PROVIDE( __data_source = LOADADDR(.data) );
  PROVIDE( __data_source_end = __tdata_source_end );
  PROVIDE( __data_source_size = __data_source_end - __data_source );


  .noncacheable :
  {
    . = ALIGN(8);
    __snoncacheable = .;/* create symbol for start of section */
    KEEP(*(.noncacheable))
    . = ALIGN(8);
    __enoncacheable = .;  /* create symbol for end of section */
  } >SRAM

  /* Uninitialized TLS data section */
  .tbss (NOLOAD) : ALIGN(4)
  {
    _sbss = .;         /* define a global symbol at bss start */
    __bss_start__ = _sbss;
    *(.tbss .tbss.*)
    . = ALIGN(4);
    PROVIDE( __tbss_end = . );
  } >SRAM

  PROVIDE( __tbss_start = ADDR(.tbss) );
  PROVIDE( __tbss_size = __tbss_end - __tbss_start );
  PROVIDE( __tbss_offset = ADDR(.tbss) - ADDR(.tdata) );

  PROVIDE( __tls_base = __tdata_start );
  PROVIDE( __tls_end = __tbss_end );
  PROVIDE( __tls_size = __tls_end - __tls_base );
  PROVIDE( __tls_align = MAX(ALIGNOF(.tdata), ALIGNOF(.tbss)) );
  PROVIDE( __tls_size_align = (__tls_size + __tls_align - 1) & ~(__tls_align - 1) );
  PROVIDE( __arm32_tls_tcb_offset = MAX(8, __tls_align) );
  PROVIDE( __arm64_tls_tcb_offset = MAX(16, __tls_align) );

  .bss (NOLOAD) : ALIGN(4)
  {
    /* This is used by the startup in order to initialize the .bss section */
    *(.bss)
    *(.bss*)
    *(COMMON)

    . = ALIGN(4);
    _ebss = .;         /* define a global symbol at bss end */
    __bss_end__ = _ebss;
      PROVIDE( __bss_end = .);
  } >SRAM
  PROVIDE( __non_tls_bss_start = ADDR(.bss) );

  PROVIDE( __bss_start = __tbss_start );
  PROVIDE( __bss_size = __bss_end - __bss_start );


  /* User_heap_stack section, used to check that there is enough SRAM left */
  ._user_heap_stack (NOLOAD) :
  {
    . = ALIGN(8);
    PROVIDE ( end = . );
    PROVIDE ( _end = . );
    . = . + _Min_Heap_Size;
    . = . + _Min_Stack_Size;
    . = ALIGN(8);
  } >SRAM

  /* Remove information from the compiler libraries */
  /DISCARD/ :
  {
    libc.a:* ( * )
    libm.a:* ( * )
    libgcc.a:* ( * )
  }

  .ARM.attributes 0 : { *(.ARM.attributes) }
}
