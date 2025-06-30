/******************************************************************************/
/*! @addtogroup Group2
    @file       thread.h
    @brief      
    @date       2025/06/30
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _THREAD_H_
#define _THREAD_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "stdint.h"
/* CODE */
void thread_start();
int thread_create(void (*run)(void *), void *userdata);
void thread_kill(uint32_t thread_id);
void thread_self_terminal();

#ifdef __cplusplus
}
#endif
#endif
