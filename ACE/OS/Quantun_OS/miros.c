/******************************************************************************/
/*! @addtogroup Group2
    @file       miros.c
    @brief      
    @date       2025/06/05
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "qassert.h"
#include "miros.h"

OSThread * volatile OS_curr;
OSThread * volatile OS_next;


