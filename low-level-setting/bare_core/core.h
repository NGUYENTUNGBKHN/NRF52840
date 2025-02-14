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
/* for Variable */
#define __I     volatile const  /* Only read */
#define __O     volatile        /* Only write */
#define __IO    volatile        /* Read Write */
/* FOr struct member */
#define __IM    volatile const  /* Only read */
#define __OM    volatile        /* Only write */
#define __IOM   volatile        /* Read wirte */



/* System Control Register */

typedef struct SCB_s
{
	__IM uint32_t CPUID;			/*!< Offset: 0x000 (R/ )  CPUID Base Register */
	__IOM uint32_t ICSR;			/*!< Offset: 0x004 (R/W)  Interrupt Control and State Register */
	__IOM uint32_t VTOR;			/*!< Offset: 0x008 (R/W)  Vector Table Offset Register */
	__IOM uint32_t AIRCR;			/*!< Offset: 0x00C (R/W)  Application Interrupt and Reset Control Register */
	__IOM uint32_t SCR;				/*!< Offset: 0x010 (R/W)  System Control Register */
	__IOM uint32_t CCR;				/*!< Offset: 0x014 (R/W)  Configuration Control Register */
	__IOM uint8_t SHP[12U]; 		/*!< Offset: 0x018 (R/W)  System Handlers Priority Registers (4-7, 8-11, 12-15) */
	__IOM uint32_t SHCSR;			/*!< Offset: 0x024 (R/W)  System Handler Control and State Register */
	__IOM uint32_t CFSR;			/*!< Offset: 0x028 (R/W)  Configurable Fault Status Register */
	__IOM uint32_t HFSR;			/*!< Offset: 0x02C (R/W)  HardFault Status Register */
	__IOM uint32_t DFSR;			/*!< Offset: 0x030 (R/W)  Debug Fault Status Register */
	__IOM uint32_t MMFAR;			/*!< Offset: 0x034 (R/W)  MemManage Fault Address Register */
	__IOM uint32_t BFAR;			/*!< Offset: 0x038 (R/W)  BusFault Address Register */
	__IOM uint32_t AFSR;			/*!< Offset: 0x03C (R/W)  Auxiliary Fault Status Register */
	__IM uint32_t PFR[2U];			/*!< Offset: 0x040 (R/ )  Processor Feature Register */
	__IM uint32_t DFR;				/*!< Offset: 0x048 (R/ )  Debug Feature Register */
	__IM uint32_t ADR;				/*!< Offset: 0x04C (R/ )  Auxiliary Feature Register */
	__IM uint32_t MMFR[4U]; 		/*!< Offset: 0x050 (R/ )  Memory Model Feature Register */
	__IM uint32_t ISAR[5U]; 		/*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register */
	uint32_t RESERVED0[5U];
	__IOM uint32_t CPACR; 			/*!< Offset: 0x088 (R/W)  Coprocessor Access Control Register */
} scb_t;

#define SCR_BASE_ADDR 0xE000ED00UL

#define SCB		((scb_t *)SCR_BASE_ADDR)
/* End */

/* FPU */

/**
 * 
 */
__STATIC_INLINE void __FPU_Enable(void)
{
	/* Enable CP10 and CP11 coprocessors */
	SCB->CPACR |= (0xFUL << 20);
	// __DSB();
	// __ISB();
}

// /**
//   \brief   Set Interrupt Vector
//   \details Sets an interrupt vector in SRAM based interrupt vector table.
// 		   The interrupt number can be positive to specify a device specific interrupt,
// 		   or negative to specify a processor exception.
// 		   VTOR must been relocated to SRAM before.
//   \param [in]   IRQn      Interrupt number
//   \param [in]   vector    Address of interrupt handler function
//  */
// __STATIC_INLINE void __NVIC_SetVector(uint32_t IRQn, uint32_t vector)
// {
// 	uint32_t vectors = (uint32_t)SCB->VTOR;
// 	(*(int *)(vectors + ((int32_t)IRQn + NVIC_USER_IRQ_OFFSET) * 4)) = vector;
	
// }

// /**
//   \brief   Get Interrupt Vector
//   \details Reads an interrupt vector from interrupt vector table.
// 		   The interrupt number can be positive to specify a device specific interrupt,
// 		   or negative to specify a processor exception.
//   \param [in]   IRQn      Interrupt number.
//   \return                 Address of interrupt handler function
//  */
// __STATIC_INLINE uint32_t __NVIC_GetVector(uint32_t IRQn)
// {
// 	uint32_t vectors = (uint32_t)SCB->VTOR;
// }

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