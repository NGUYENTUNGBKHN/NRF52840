/******************************************************************************/
/*! @addtogroup Group2
    @file       common.h
    @brief      
    @date       2024/06/19
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

/* CODE */
#include <stdint.h>
/* for Variable */
#define __I     volatile const  /* Only read */
#define __O     volatile        /* Only write */
#define __IO    volatile        /* Read Write */
/* FOr struct member */
#define __IM    volatile const  /* Only read */
#define __OM    volatile        /* Only write */
#define __IOM   volatile        /* Read wirte */


/* UART Register*/
#define UART_BASE_ADDRESS 0x40002000



#ifdef __cplusplus
}
#endif
#endif



