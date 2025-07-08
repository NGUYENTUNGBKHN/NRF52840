/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_initialize_kernel_enter.c
    @brief      
    @date       2025/07/08
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "ace_api.h"
#include "ace_thread.h"

void _ace_initialize_kernel_enter(void)
{
    _ace_thread_current_ptr = NULL;
    _ace_thread_schedule();
}


