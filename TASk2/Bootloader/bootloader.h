/******************************************************************************/
/*! @addtogroup Group2
    @file       bootloader.h
    @brief      
    @date       2025/02/03
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_
#ifdef __cplusplus
extern "C"
{
#endif
#include "core.h"

/* defined step mode */
enum STEP_MODE
{
    STEP_BOOT_IDLE,
    STEP_BOOT_CMD_FREE,
    STEP_BOOT_DL_START,
    STEP_BOOT_DL_DATA,
    STEP_BOOT_DL_CRC_CHECK,
    STEP_MODE_DL_END
};

enum BOOT_MSG
{
    BOOT_MSG_SUCCESS,
    BOOT_MSG_ALARM,
    BOOT_MSG_ERROR
};
/* CODE */
extern void bootloader();



#ifdef __cplusplus
}
#endif
#endif

