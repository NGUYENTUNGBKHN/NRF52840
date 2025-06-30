/******************************************************************************/
/*! @addtogroup Group2
    @file       asm.h
    @brief      
    @date       2025/06/30
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _ASM_H_
#define _ASM_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include <stdint.h>
/* CODE */
extern uint32_t *activate(uint32_t *a);
extern void syscall(void);


#ifdef __cplusplus
}
#endif
#endif