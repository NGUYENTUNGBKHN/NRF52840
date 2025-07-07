/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_port.h
    @brief      
    @date       2025/07/03
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _ACE_PORT_H_
#define _ACE_PORT_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#undef ACE_PORT_USE_BASEPRI

/* Define the interrupt disable/restore macros for each compiler. */

__attribute__( ( always_inline ) ) static inline uint32_t __get_interrupt_posture()
{
    uint32_t posture;
#ifdef ACE_PORT_USE_BASE_PRI
    __asm__ volatile ("MRS %0, BASRPRI": "=r" (posture));
#else
    __asm__ volatile ("MRS %0, PRIMASK": "=r" (posture));
#endif
    return posture;
}

#ifdef ACE_PORT_USE_BASEPRI
__attribute__( ( always_inline ) ) static inline void __set_basepri_value(uint32_t basepri_value)
{

}
#else
__attribute__( ( always_inline ) ) static inline void __enable_interrupt()
{
    __asm__ volatile ("CPSIE i": : : "memory");
}
#endif

__attribute__( ( always_inline ) ) static inline void __restore_interrupt(uint32_t int_posture)
{
#ifdef ACE_PORT_USE_BASEPRI
    __set_basepri_value(int_posture);
#else
    __asm__ volatile ("MSR PRIMASK, %0": : "r" (int_posture): "memory");
#endif    
}

__attribute__( ( always_inline ) ) static inline uint32_t __disable_interrupt()
{
    uint32_t posture;
    posture = __get_interrupt_posture();
#ifdef ACE_PORT_USE_BASEPRI
    __set_basepri_value(posture);
#else
    __asm__ volatile ("CPSID i" : : : "memory");
#endif
    return posture;
}

__attribute__( ( always_inline ) ) static inline void  _ace_thread_system_return_inline()
{
    
}

#define ACE_INTERRUPT_SAVE_AREA         uint32_t interrupt_save;
#define ACE_DISABLE                     interrupt_save = __disable_interrupt();
#define ACE_RESTORE                     __restore_interrupt(interrupt_save);




#ifdef __cplusplus
}
#endif
#endif
