/******************************************************************************/
/*! @addtogroup Group2
    @file       boot_section_header.c
    @brief      
    @date       2024/12/04
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "common.h"
#include "memory_map.h"

__attribute((section(".BOOT_SECTION_HEADER")))
BA_SectionHeader ex_boot_header = 
{
    BA_SYMBOL,                		/* File Header						*/
	0x00000000,						/* CRC-32							*/
	0x0000,							/* CRC-16		 					*/
	0x0001,							/* section no						*/
	SWAP_ENDIAN(ADDR_BOOT_BEGIN),	/* Program start address			*/
	SWAP_ENDIAN(ADDR_BOOT_END),		/*    	  end address				*/
	0x00000000,						/* Program size						*/
	"BOOT",							/* section name						*/
	0x00000000,						/* reserve							*/
	0x00000000,						/* reserve							*/
};



