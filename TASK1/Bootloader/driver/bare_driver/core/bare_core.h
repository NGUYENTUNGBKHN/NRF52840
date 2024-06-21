/******************************************************************************/
/*! @addtogroup Group2
    @file       bare_core.h
    @brief      
    @date       2024/06/21
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _BARE_CORE_H_
#define _BARE_CORE_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
/* CODE */
/* specific define */
#ifndef __STATIC_INLINE 
#define __STATIC_INLINE static __inline 
#endif 

#ifndef __ASM
#define __ASM           __asm
#endif

__STATIC_INLINE uint32_t __get_MSP(void)
{
  register uint32_t __regMainStackPointer     __ASM("msp");
  return(__regMainStackPointer);
}

__STATIC_INLINE void __set_MSP(uint32_t topOfMainStack)
{
    register uint32_t __regMainStackPointer __ASM("msp");
    __regMainStackPointer = topOfMainStack;
}



#ifdef __cplusplus
}
#endif
#endif
