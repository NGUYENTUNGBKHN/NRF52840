/******************************************************************************/
/*! @addtogroup Group2
    @file       common.h
    @brief      
    @date       2024/12/06
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _COMMON_H_
#define _COMMON_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>

#define BA_SYMBOL		"VFM21   "
#define SWAP_ENDIAN(adr)	( (((uint32_t)(adr) & 0xff000000) >> 24) | (((uint32_t)(adr) & 0xff0000) >> 8) | (((uint32_t)(adr) & 0xff00) << 8) | (((uint32_t)(adr) & 0xff) << 24) )

/* CODE */
/*----------------------------------------------------------*/
/*			Section Header										*/
/*----------------------------------------------------------*/
typedef struct {
	uint8_t fileheader[8];			    /* Section Header						*/
	uint32_t crc32;					    /* CRC-32							*/
	uint16_t crc16;					    /* CRC-16		 					*/
	uint16_t sec_no;					/* section no						*/
	uint32_t startadr;				    /* Program start address			*/
	uint32_t endadr;					/*    	  end address				*/
	uint32_t sec_size;				    /* Program size						*/
	uint8_t sec_name[4];				/* section name						*/
	uint32_t dummy3;					/* reserve							*/
	uint32_t dummy4;					/* reserve							*/
}BA_SectionHeader;


#ifdef __cplusplus
}
#endif
#endif
