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

#define ARM_GCC_COMPILER

/* Compiler specific defines */
#ifndef   __ASM
  #define __ASM                                  __asm
#endif
#ifndef   __INLINE
  #define __INLINE                               inline
#endif
#ifndef   __STATIC_INLINE
  #define __STATIC_INLINE                        static inline
#endif
#ifndef   __STATIC_FORCEINLINE                 
  #define __STATIC_FORCEINLINE                   __attribute__((always_inline)) static inline
#endif                                           
#ifndef   __NO_RETURN
  #define __NO_RETURN                            __attribute__((__noreturn__))
#endif
#ifndef   __USED
  #define __USED                                 __attribute__((used))
#endif
#ifndef   __WEAK
  #define __WEAK                                 __attribute__((weak))
#endif
#ifndef   __PACKED
  #define __PACKED                               __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_STRUCT
  #define __PACKED_STRUCT                        struct __attribute__((packed, aligned(1)))
#endif
#ifndef   __PACKED_UNION
  #define __PACKED_UNION                         union __attribute__((packed, aligned(1)))
#endif
/* End */

__STATIC_INLINE uint32_t __get_MSP(void)
{
    #if defined(ARM_GCC_COMPILER)
    uint32_t result;
    __ASM volatile("MRS %0, msp" : "=r" (result));
    return result;
    #else
    register uint32_t __regMainStackPointer __ASM("msp");
    return (__regMainStackPointer);
    #endif 
    
}
    
__STATIC_FORCEINLINE void __set_MSP(uint32_t topOfMainStack)
{
    #if defined(ARM_GCC_COMPILER)
    __ASM volatile("MSR msp, %0" : : "r"(topOfMainStack) :);
    #else
    register uint32_t __regProcessStackPointer  __ASM("psp");
    __regProcessStackPointer = topOfProcStack;
    #endif 
}

/******************************************************************************/
/*! @addtogroup Group2
    @brief      Set Control Register
    
    @param control 
    @return __STATIC_INLINE 
******************************************************************************/
__STATIC_INLINE void __set_CONTROL(uint32_t control)
{
    #if defined(ARM_GCC_COMPILER)
    __ASM volatile ("MSR control, %0" : : "r" (control) : "memory" );
    #else
    #endif 
}

/******************************************************************************/
/*! @addtogroup Group2
    @brief      Set Priority Mark
    
    @param priMask 
    @return __STATIC_FORCEINLINE 
******************************************************************************/
__STATIC_FORCEINLINE void __set_PRIMASK(uint32_t priMask)
{
    #if defined(ARM_GCC_COMPILER)
    __ASM volatile ("MSR primask, %0" : : "r" (priMask) : "memory");
    #else
    #endif 
}


/******************************************************************************/
/*! @addtogroup Group2
    @brief      Set Base Priority
    
    @param basePri 
    @return __STATIC_FORCEINLINE 
******************************************************************************/
__STATIC_FORCEINLINE void __set_BASEPRI(uint32_t basePri)
{
    #if defined(ARM_GCC_COMPILER)
    __ASM volatile ("MSR basepri, %0" : : "r" (basePri) : "memory");
    #else
    #endif
}

__STATIC_FORCEINLINE void __set_FAULTMASK(uint32_t faultMask)
{
    #if defined(ARM_GCC_COMPILER)
    __ASM volatile ("MSR faultmask, %0" : : "r" (faultMask) : "memory");
    #else
    #endif
}

#ifdef __cplusplus
}
#endif
#endif