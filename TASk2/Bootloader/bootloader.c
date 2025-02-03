/******************************************************************************/
/*! @addtogroup Group2
    @file       bootloader.c
    @brief      
    @date       2025/02/03
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#include "bootloader.h"

static uint32_t step_boot;
static uint32_t bootloader_main_msg;

static void bootloader_get_msg(uint32_t *msg);
static void bootloader_set_msg(uint32_t msg);
static void bootloader_change_mode(uint32_t mode);
static void bootloader_idle(uint32_t msg);
static void bootloader_cmd_free(uint32_t msg);
static void bootloader_start(uint32_t msg);
static void bootloader_data(uint32_t msg);
static void bootloader_check_crc(uint32_t msg);
static void bootloader_end(uint32_t msg);

void bootloader()
{
    step_boot = STEP_BOOT_IDLE;
    uint32_t msg;
    /* initialized more one uart */

    /*  */
    while (1)
    {
        bootloader_get_msg(&msg);
        /* code */
        switch (step_boot)
        {
        case STEP_BOOT_IDLE:
            bootloader_idle(msg);
            break;
        case STEP_BOOT_CMD_FREE:
            bootloader_cmd_free(msg);
            break;
        case STEP_BOOT_DL_START:
            bootloader_start(msg);
            break;
        case STEP_BOOT_DL_DATA:
            bootloader_data(msg);
            break;
        case STEP_BOOT_DL_CRC_CHECK:
            bootloader_check_crc(msg);
            break;
        case STEP_MODE_DL_END:
            bootloader_end(msg);
            break;
        default:
            break;
        }
    }
}

static void bootloader_get_msg(uint32_t *msg)
{
    msg = bootloader_main_msg;
}

static void bootloader_set_msg(uint32_t msg)
{
    if (msg > BOOT_MSG_ERROR || msg < BOOT_MSG_SUCCESS)
    {
        return ;
    }

    bootloader_main_msg = msg;
}

static void bootloader_change_mode(uint32_t mode)
{
    if (mode > STEP_MODE_DL_END || mode < STEP_BOOT_IDLE)
    {
        return;
    }
    step_boot = mode;
}

static void bootloader_idle(uint32_t msg)
{
    switch (msg)
    {
    case BOOT_MSG_SUCCESS:
        break;
    case BOOT_MSG_ALARM:
        break;
    case BOOT_MSG_ERROR:
        break;
    default:
        break;
    }
}

static void bootloader_cmd_free(uint32_t msg)
{
    switch (msg)
    {
    case BOOT_MSG_SUCCESS:
        break;
    case BOOT_MSG_ALARM:
        break;
    case BOOT_MSG_ERROR:
        break;
    default:
        break;
    }
}

static void bootloader_start(uint32_t msg)
{
    switch (msg)
    {
    case BOOT_MSG_SUCCESS:
        break;
    case BOOT_MSG_ALARM:
        break;
    case BOOT_MSG_ERROR:
        break;
    default:
        break;
    }
}

static void bootloader_data(uint32_t msg)
{
    switch (msg)
    {
    case BOOT_MSG_SUCCESS:
        break;
    case BOOT_MSG_ALARM:
        break;
    case BOOT_MSG_ERROR:
        break;
    default:
        break;
    }
}

static void bootloader_check_crc(uint32_t msg)
{
    switch (msg)
    {
    case BOOT_MSG_SUCCESS:
        break;
    case BOOT_MSG_ALARM:
        break;
    case BOOT_MSG_ERROR:
        break;
    default:
        break;
    }
}

static void bootloader_end(uint32_t msg)
{
    switch (msg)
    {
    case BOOT_MSG_SUCCESS:
        break;
    case BOOT_MSG_ALARM:
        break;
    case BOOT_MSG_ERROR:
        break;
    default:
        break;
    }
}
