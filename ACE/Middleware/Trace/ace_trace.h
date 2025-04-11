/******************************************************************************/
/*! @addtogroup Group2
    @file       ace_trace.h
    @brief      
    @date       2025/04/11
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _ACE_TRACE_H_
#define _ACE_TRACE_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include <stdint.h>
#include "External/segger_rtt/SEGGER_RTT.h"


extern void ace_trace_init(void);
// extern void ace_trace_log(const char *format, ...);
extern uint8_t ace_trace_is_init;


#define ace_trace_log(format, ...) \
    do { \
        if (ace_trace_is_init) { \
            SEGGER_RTT_printf(0, format, ##__VA_ARGS__); \
        } \
    } while (0)

#ifdef __cplusplus
}
#endif
#endif

