/******************************************************************************/
/*! @addtogroup Group2
    @file       main.h
    @brief      
    @date       2025/07/14
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#pragma once
#include <stdio.h>

#define _DEBUG

#ifdef _DEBUG
#define TRACE_LOG(format, ...)     printf("%s(%d) -->" format, __FUNCTION__, __LINE__)
#else
#endif
