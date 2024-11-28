/******************************************************************************/
/*! @addtogroup Group2
    @file       nrf_core.h
    @brief
    @date       2024/11/28
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _NRF_CORE_H_
#define _NRF_CORE_H_
#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
    /* CODE */

#ifndef __STATIC_INLINE
#define __STATIC_INLINE static __inline
#endif

#ifndef   __STATIC_FORCEINLINE                 
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif 

#ifndef __ASM
#define __ASM asm
#endif

__STATIC_INLINE uint32_t __get_MSP(void)
{
    register uint32_t __regMainStackPointer __ASM("msp");
    return (__regMainStackPointer);
}

__STATIC_FORCEINLINE void __set_MSP(uint32_t topOfMainStack)
{
  __ASM volatile ("MSR msp, %0" : : "r" (topOfMainStack) : );
}

#ifdef __cplusplus
}
#endif
#endif