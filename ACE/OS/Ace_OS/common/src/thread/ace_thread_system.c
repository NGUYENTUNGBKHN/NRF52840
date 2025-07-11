/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_thread_system.c
    @brief      
    @date       2025/07/09
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "ace_api.h"
#include "ace_thread.h"

void _ace_thread_system_suspend(ACE_THREAD *thread_ptr)
{
    ACE_INTERRUPT_SAVE_AREA
    ACE_THREAD       *current_thread;
    
    ACE_THREAD_GET_CURRENT(current_thread)

    ACE_DISABLE

    thread_ptr->ace_thread_state = ACE_SUSPENDED;

    if (_ace_thread_created_count > 1)
    {
        ACE_THREAD *next_thread = thread_ptr->ace_thread_created_next;
        ACE_THREAD *pre_thread = thread_ptr->ace_thread_created_previous;
        // Relink neighbors around the thread being suspended
        if (pre_thread != NULL) // Defensive check, should not be NULL in a circular list
        { 
            pre_thread->ace_thread_created_next = next_thread;
        }
        if (next_thread != NULL) // Defensive check
        { 
                
            next_thread->ace_thread_created_previous = pre_thread;
        }

        // If the suspended thread was the head of the 'created' list, update the head.
        if (_ace_thread_created_ptr == thread_ptr) 
        {
            _ace_thread_created_ptr = next_thread;
        }
    }
    else
    {
        _ace_thread_created_ptr = NULL;
    }
    // Decrement the count of "active" or "schedulable" threads in this model.
    _ace_thread_created_count--;

    // 4. Clear the suspended thread's 'created' list pointers.
    // This detaches the thread completely from the list.
    thread_ptr->ace_thread_created_next = NULL;
    thread_ptr->ace_thread_created_previous = NULL;
    ACE_RESTORE
    // 5. If the suspended thread was the currently executing thread,
    // we need to trigger a context switch to find the next active thread.
    if (current_thread == thread_ptr) 
    {
        _ace_thread_current_ptr = NULL;
        _ace_thread_system_return();
    }
}

void _ace_thread_system_resume(ACE_THREAD *thread_ptr)
{
    ACE_INTERRUPT_SAVE_AREA



    ACE_DISABLE

    ACE_RESTORE
}

