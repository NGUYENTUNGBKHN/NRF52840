/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_common.h
    @brief      
    @date       2025/04/25
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_COMMON_H_
#define _HAL_COMMON_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "nrf52840.h"
#include "nrf52840_bitfields.h"
#include "stdbool.h"
#include "stddef.h"

/**
 * @brief Macro for getting the offset (in bytes) from the beginning of a structure
 *        of the specified type to its specified member.
 *
 * @param[in] type   Structure type.
 * @param[in] member Structure member whose offset is searched for.
 *
 * @return Member offset in bytes.
 */
#define HAL_OFFSETOF(type, member)  ((size_t)&(((type *)0)->member))

#ifdef __cplusplus
}
#endif
#endif
