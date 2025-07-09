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


/* Thread execution state values.  */

#define ACE_READY                        ((uint32_t) 0)
#define ACE_COMPLETED                    ((uint32_t) 1)
#define ACE_TERMINATED                   ((uint32_t) 2)
#define ACE_SUSPENDED                    ((uint32_t) 3)
#define ACE_SLEEP                        ((uint32_t) 4)
#define ACE_QUEUE_SUSP                   ((uint32_t) 5)
#define ACE_SEMAPHORE_SUSP               ((uint32_t) 6)
#define ACE_EVENT_FLAG                   ((uint32_t) 7)
#define ACE_BLOCK_MEMORY                 ((uint32_t) 8)
#define ACE_BYTE_MEMORY                  ((uint32_t) 9)
#define ACE_IO_DRIVER                    ((uint32_t) 10)
#define ACE_FILE                         ((uint32_t) 11)
#define ACE_TCP_IP                       ((uint32_t) 12)
#define ACE_MUTEX_SUSP                   ((uint32_t) 13)
#define ACE_PRIORITY_CHANGE              ((uint32_t) 14)

/* API return values.  */

#define ACE_SUCCESS                      ((uint32_t) 0x00)
#define ACE_DELETED                      ((uint32_t) 0x01)
#define ACE_POOL_ERROR                   ((uint32_t) 0x02)
#define ACE_PTR_ERROR                    ((uint32_t) 0x03)
#define ACE_WAIT_ERROR                   ((uint32_t) 0x04)
#define ACE_SIZE_ERROR                   ((uint32_t) 0x05)
#define ACE_GROUP_ERROR                  ((uint32_t) 0x06)
#define ACE_NO_EVENTS                    ((uint32_t) 0x07)
#define ACE_OPTION_ERROR                 ((uint32_t) 0x08)
#define ACE_QUEUE_ERROR                  ((uint32_t) 0x09)
#define ACE_QUEUE_EMPTY                  ((uint32_t) 0x0A)
#define ACE_QUEUE_FULL                   ((uint32_t) 0x0B)
#define ACE_SEMAPHORE_ERROR              ((uint32_t) 0x0C)
#define ACE_NO_INSTANCE                  ((uint32_t) 0x0D)
#define ACE_THREAD_ERROR                 ((uint32_t) 0x0E)
#define ACE_PRIORITY_ERROR               ((uint32_t) 0x0F)
#define ACE_NO_MEMORY                    ((uint32_t) 0x10)
#define ACE_START_ERROR                  ((uint32_t) 0x10)
#define ACE_DELETE_ERROR                 ((uint32_t) 0x11)
#define ACE_RESUME_ERROR                 ((uint32_t) 0x12)
#define ACE_CALLER_ERROR                 ((uint32_t) 0x13)
#define ACE_SUSPEND_ERROR                ((uint32_t) 0x14)
#define ACE_TIMER_ERROR                  ((uint32_t) 0x15)
#define ACE_TICK_ERROR                   ((uint32_t) 0x16)
#define ACE_ACTIVATE_ERROR               ((uint32_t) 0x17)
#define ACE_THRESH_ERROR                 ((uint32_t) 0x18)
#define ACE_SUSPEND_LIFTED               ((uint32_t) 0x19)
#define ACE_WAIT_ABORTED                 ((uint32_t) 0x1A)
#define ACE_WAIT_ABORT_ERROR             ((uint32_t) 0x1B)
#define ACE_MUTEX_ERROR                  ((uint32_t) 0x1C)
#define ACE_NOT_AVAILABLE                ((uint32_t) 0x1D)
#define ACE_NOT_OWNED                    ((uint32_t) 0x1E)
#define ACE_INHERIT_ERROR                ((uint32_t) 0x1F)
#define ACE_NOT_DONE                     ((uint32_t) 0x20)
#define ACE_CEILING_EXCEEDED             ((uint32_t) 0x21)
#define ACE_INVALID_CEILING              ((uint32_t) 0x22)
#define ACE_FEATURE_NOT_ENABLED          ((uint32_t) 0xFF)

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
    uint32_t ace_thread_state;
    void    (*ace_thread_entry)(uint32_t id);
    uint32_t ace_thread_entry_parameter;
}ACE_THREAD;


typedef struct ACE_BYTE_POOL_STRUCT_S
{
    uint8_t *ace_byte_pool_list;
    void    *ace_byte_pool_start;
    uint32_t ace_byte_pool_size;
    struct ACE_BYTE_POOL_STRUCT_S
            *ace_byte_pool_created_next,
            *ace_byte_pool_created_previous;
}ACE_BYTE_POOL;

/* ACE thread initialize */
void _ace_initialize_kernel_enter(void);

/* Thread portion */
uint32_t _ace_thread_create(ACE_THREAD *thread_ptr, char *name_thread, uint32_t stack_size, void (*entry_thread)(uint32_t));
uint32_t _ace_thread_suspend(ACE_THREAD *thread_ptr);

/* Byte pool portion */



#ifdef __cplusplus
}
#endif
#endif

