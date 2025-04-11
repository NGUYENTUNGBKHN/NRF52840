/******************************************************************************/
/*! @addtogroup Group2
    @file       log.h
    @brief      
    @date       2024/11/19
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _LOG_H_
#define _LOG_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
void logInit();

int logPrintf(const char *str);

#ifdef __cplusplus
}
#endif
#endif
