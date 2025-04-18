/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_common.h
    @brief      
    @date       2025/04/16
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_COMMON_H_
#define _DRV_COMMON_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */

typedef enum DRV_STA_s
{
    DRV_STA_OK = 0,     /* 0x00 : No error */        
    DRV_STA_NG = -1,    /* 0xFF : Error  */
}DRV_STA_t;

#ifdef __cplusplus
}
#endif
#endif


