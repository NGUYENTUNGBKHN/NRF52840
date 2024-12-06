/******************************************************************************/
/*! @addtogroup Group2
    @file       app_section_header.c
    @brief      
    @date       2024/12/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/


#include "common.h"
#include "memory_map.h"

__attribute((section(".APP_SECTION_HEADER")))
BA_SectionHeader ex_boot_header = 
{
    BA_SYMBOL,                		/* File Header						*/
	0x00000000,						/* CRC-32							*/
	0x0000,							/* CRC-16		 					*/
	0x0002,							/* section no						*/
	SWAP_ENDIAN(ADDR_APP_SECTION),	/* Program start address			*/
	SWAP_ENDIAN(ADDR_APP_END),		/*    	  end address				*/
	0x00000000,						/* Program size						*/
	"APP1",							/* section name						*/
	0x00000000,						/* reserve							*/
	0x00000000,						/* reserve							*/
};

