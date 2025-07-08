/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_api.h
    @brief      
    @date       2025/07/03
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _ACE_API_H_
#define _ACE_API_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "ace_port.h"

typedef struct ACE_THREAD_STRUCT_S
{
    uint32_t ace_thread_id;
    uint32_t ace_thread_run_counter;
    void    *ace_thread_stack_ptr;
    void    *ace_thread_stack_start;
    void    *ace_thread_stack_end;
    uint32_t ace_thread_stack_size;
    uint8_t  ace_in_use;
    struct ACE_THREAD_STRUCT_S
            *ace_thread_created_next,
            *ace_thread_created_previous;
}ACE_THREAD;


uint32_t _ace_thread_create(ACE_THREAD *thread_ptr, char *name_thread, uint32_t stack_size, void (*entry_thread)(void*));
void _ace_initialize_kernel_enter(void);

#ifdef __cplusplus
}
#endif
#endif

