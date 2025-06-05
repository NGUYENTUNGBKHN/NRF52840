/******************************************************************************/
/*! @addtogroup Group2
    @file       miros.h
    @brief      
    @date       2025/06/05
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _MIROS_H_
#define _MIROS_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include <stdint.h>

/* Thread Control Block (TCB) */
typedef struct {
    void *sp;           /* stack pointer */
    uint32_t timeout;   /* timeout delay down-counter */
    uint8_t prio;       /* thread priority */
} OSThread;

typedef void (*OSThreadHandler)();

void OS_init(void *stkSto, uint32_t stkSize);

/* callback to handle the idle condition */
void OS_onIdle(void);

/* this function must be called with interrupts DISABLED */
void OS_sched(void);

/* transfer control to the RTOS to run the threads */
void OS_run(void);

/* blocking delay */
void OS_delay(uint32_t ticks);

/* process all timeouts */
void OS_tick(void);

/* callback to configure and start interrupts */
void OS_onStartup(void);

void OSThread_start(
    OSThread *me,
    uint8_t prio, /* thread priority */
    OSThreadHandler threadHandler,
    void *stkSto, uint32_t stkSize);



#ifdef __cplusplus
}
#endif
#endif
