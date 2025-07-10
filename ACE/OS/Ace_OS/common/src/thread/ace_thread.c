/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_thread.c
    @brief      
    @date       2025/07/03
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "ace_api.h"
#include "ace_thread.h"

uint32_t _ace_thread_created_count = 0;

void _ace_thread_exit();

ACE_THREAD *_ace_thread_current_ptr;
ACE_THREAD *_ace_thread_created_ptr;
uint32_t _ace_thread_system_state;

void _ace_thread_shell_entry(void)
{
    ACE_INTERRUPT_SAVE_AREA

    ACE_THREAD *thread_ptr;

    ACE_THREAD_GET_CURRENT(thread_ptr);

    /* Call current thread's entry function.  */
    thread_ptr->ace_thread_entry(thread_ptr->ace_thread_entry_parameter);

    ACE_DISABLE

    thread_ptr->ace_thread_state = ACE_COMPLETED;
    thread_ptr->ace_in_use = 0;
    free(thread_ptr->ace_thread_stack_start);

    ACE_RESTORE

    // suspend thread

}

/* Build a fake interrupt frame. The form of the fake interrupt stack 
    on the Cortex-M should look like the following after it is built :
    
    Stack top:   n = STACK_SIZE - 1
        1                   .
        .                   .
        .                   .
        .                   .
        n - 17              R4
        n - 16              R5
        n - 14              R6
        n - 13              R7
        n - 12              R8
        n - 11              R9
        n - 10              R10
        n - 9               R11
        n - 8               LR
        n - 7               R0
        n - 6               R1
        n - 5               R2
        n - 4               R3
        n - 3               R12
        n - 2               lr
        n - 1               pc
        n                   xPSR
    */
uint32_t _ace_thread_create(ACE_THREAD *thread_ptr, char *name_thread, 
                            uint32_t stack_size, void (*entry_thread)(uint32_t))
{
    uint32_t *stack;
    ACE_THREAD *next_thread;
    ACE_THREAD *pre_thread;

    ACE_INTERRUPT_SAVE_AREA
    ACE_DISABLE

    /* Allocate dynamic memory for thread stack */
    stack = (uint32_t*)malloc(stack_size* sizeof(uint32_t)); 
    
    if (stack == NULL)
    {
        return ACE_THREAD_ERROR;
    }
    thread_ptr->ace_thread_id = _ace_thread_created_count + 1;
    thread_ptr->ace_thread_entry_parameter = _ace_thread_created_count + 1;
    thread_ptr->ace_thread_stack_start = stack;
    thread_ptr->ace_thread_entry = entry_thread;
    stack += (stack_size - 17);
    thread_ptr->ace_thread_stack_ptr = stack;
    *stack++ = (uint32_t)(0);                       /* R4 */
    *stack++ = (uint32_t)(0);                       /* R5 */
    *stack++ = (uint32_t)(0);                       /* R6 */
    *stack++ = (uint32_t)(0);                       /* R7 */
    *stack++ = (uint32_t)(0);                       /* R8 */
    *stack++ = (uint32_t)(0);                       /* R9 */
    *stack++ = (uint32_t)(0);                       /* R10 */
    *stack++ = (uint32_t)(0);                       /* R11 */
    *stack++ = (uint32_t)(THREAD_PSP);              /* LR */
    *stack++ = (uint32_t)(0);                       /* R0 */
    *stack++ = (uint32_t)(0);                       /* R1 */
    *stack++ = (uint32_t)(0);                       /* R2 */
    *stack++ = (uint32_t)(0);                       /* R3 */
    *stack++ = (uint32_t)(0);                       /* R12 */
    *stack++ = (uint32_t)(0);                       /* lr */
    *stack++ = (uint32_t)&_ace_thread_shell_entry;  /* pc */
    *stack   = (uint32_t)0x01000000;                /* xPSR */
    thread_ptr->ace_thread_stack_end = stack;
    thread_ptr->ace_in_use = 1;


    // thread_ptr

    if (_ace_thread_created_count == 0)
    {
        /* The created thread list is empty. Add thread to empty list. */
        _ace_thread_created_ptr = thread_ptr;
        thread_ptr->ace_thread_created_next = thread_ptr;
        thread_ptr->ace_thread_created_previous = thread_ptr;
    }
    else
    {
        next_thread = _ace_thread_created_ptr;
        pre_thread = _ace_thread_created_ptr->ace_thread_created_previous;

        next_thread->ace_thread_created_previous = thread_ptr;
        pre_thread->ace_thread_created_next = thread_ptr;

        thread_ptr->ace_thread_created_previous = pre_thread;
        thread_ptr->ace_thread_created_next = next_thread;
    }

    _ace_thread_created_count++;
    ACE_RESTORE

    return ACE_SUCCESS;
}

uint32_t _ace_thread_delete(ACE_THREAD *thread_ptr)
{
    ACE_THREAD *next_thread;
    ACE_THREAD *pre_thread;
    ACE_INTERRUPT_SAVE_AREA
    ACE_DISABLE

    /* Clear the thread ID */
    thread_ptr->ace_thread_id = 0;
    /* Decrement the number of created threads */
    _ace_thread_created_count --;

    if (_ace_thread_created_count == 0)
    {
        _ace_thread_created_ptr = NULL;
    }
    else
    {
        next_thread = thread_ptr->ace_thread_created_next;
        pre_thread = thread_ptr->ace_thread_created_previous;
        next_thread->ace_thread_created_previous = pre_thread;
        pre_thread->ace_thread_created_next = next_thread;

        if(_ace_thread_created_ptr == thread_ptr)
        {
            _ace_thread_created_ptr = next_thread;
        }
    }

    ACE_RESTORE
    return ACE_SUCCESS;
}

uint32_t _ace_thread_reset(ACE_THREAD *thread_ptr)
{
    ACE_INTERRUPT_SAVE_AREA
    ACE_DISABLE

    uint32_t status;
    ACE_THREAD *thread_curr;
    uint32_t *stack;

    status = ACE_SUCCESS;

    ACE_THREAD_GET_CURRENT(thread_curr);
    if (thread_curr == thread_ptr)
    {
        status = ACE_NOT_DONE;
    }
    else
    {
        /* Check for proper status of this thread to reset.  */
        if (thread_ptr->ace_thread_state != ACE_COMPLETED)
        {
            /* Now check for terminated state.  */
            if (thread_ptr->ace_thread_state != ACE_TERMINATED)
            {
                /* Thread not completed or terminated - return an error!  */
                status =  ACE_NOT_DONE;
            }
        }
    }

    if (status == ACE_SUCCESS)
    {
        /* Modify the thread status to prevent additional reset calls. */
        thread_ptr->ace_thread_state = ACE_NOT_DONE;
        ACE_RESTORE
        stack = thread_ptr->ace_thread_stack_ptr;
        *stack++ = (uint32_t)(0);                       /* R4 */
        *stack++ = (uint32_t)(0);                       /* R5 */
        *stack++ = (uint32_t)(0);                       /* R6 */
        *stack++ = (uint32_t)(0);                       /* R7 */
        *stack++ = (uint32_t)(0);                       /* R8 */
        *stack++ = (uint32_t)(0);                       /* R9 */
        *stack++ = (uint32_t)(0);                       /* R10 */
        *stack++ = (uint32_t)(0);                       /* R11 */
        *stack++ = (uint32_t)(THREAD_PSP);              /* LR */
        *stack++ = (uint32_t)(0);                       /* R0 */
        *stack++ = (uint32_t)(0);                       /* R1 */
        *stack++ = (uint32_t)(0);                       /* R2 */
        *stack++ = (uint32_t)(0);                       /* R3 */
        *stack++ = (uint32_t)(0);                       /* R12 */
        *stack++ = (uint32_t)(0);                       /* lr */
        *stack++ = (uint32_t)&_ace_thread_shell_entry;  /* pc */
        *stack   = (uint32_t)0x01000000;                /* xPSR */
        ACE_DISABLE

        thread_ptr->ace_thread_state = ACE_SUSPENDED;
    }

    ACE_RESTORE
    return status;
}

uint32_t _ace_thread_resume(ACE_THREAD *thread_ptr)
{

}

uint32_t _ace_thread_sleep(uint32_t timer_ticks)
{
    ACE_INTERRUPT_SAVE_AREA
    uint32_t status;
    ACE_THREAD *thread_ptr;


    ACE_DISABLE

    ACE_THREAD_GET_CURRENT(thread_ptr)

    if (thread_ptr == NULL)
    {
        /* Restore interrupts.  */
        ACE_RESTORE

        /* Illegal caller of this service.  */
        status =  ACE_CALLER_ERROR;
    }
    else if (timer_ticks == 0)
    {
        /* Restore interrupts.  */
        ACE_RESTORE

        /* Just return with a successful status.  */
        status = ACE_SUCCESS;
    }
    else
    {
        status = ACE_SUCCESS;
    }
    return status;
}

uint32_t _ace_thread_suspend(ACE_THREAD *thread_ptr)
{

    ACE_THREAD  *current_thread;
    uint32_t status;

    /* Pickup thread pointer.  */
    ACE_THREAD_GET_CURRENT(current_thread)

    if (thread_ptr->ace_thread_state == ACE_READY)
    {
        status = ACE_SUCCESS;
    }

    if (status == ACE_SUCCESS)
    {
        _ace_thread_system_suspend(thread_ptr);
    }

}

