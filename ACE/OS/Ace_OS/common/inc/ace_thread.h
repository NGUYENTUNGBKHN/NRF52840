/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_thread.h
    @brief      
    @date       2025/07/04
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _ACE_THREAD_H_
#define _ACE_THREAD_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#define MAX_TASKS 2

/* Exception return behavior */
#define HANDLER_MSP	0xFFFFFFF1
#define THREAD_MSP	0xFFFFFFF9 
#define THREAD_PSP	0xFFFFFFFD

extern uint32_t lastTask;
extern ACE_THREAD ace_thread[MAX_TASKS];
extern uint32_t _ace_thread_created_count;
extern ACE_THREAD *_ace_thread_creatd_ptr;

/* THREAD ERROR */
enum THREAD_ERROR_CODE
{
    THREAD_OK = 0,
    THREAD_ERROR_ID_INVALID,
    THREAD_ERROR_FAIL
};

#ifdef __cplusplus
}
#endif
#endif
