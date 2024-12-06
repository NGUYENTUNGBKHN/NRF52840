/******************************************************************************/
/*! @addtogroup Group2
    @file       memory_map.h
    @brief      
    @date       2024/11/20
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _MEMORY_MAP_H_
#define _MEMORY_MAP_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include "../bare_core/core.h"
/* CODE */




#define ADDR_BOOT_BEGIN     0x00000000
#define ADDR_BOOT_END       0x000E0000

#define ADDR_APP_SECTION    0x000E0000
#define ADDR_APP_BEGIN      0x000E0028
#define ADDR_APP_END        0x00000000

#ifdef __cplusplus
}
#endif
#endif



