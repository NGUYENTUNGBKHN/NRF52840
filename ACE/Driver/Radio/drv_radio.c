/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_radio.c
    @brief      
    @date       2025/05/13
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#include "drv_radio.h"
#include "drv_clock.h"
#include "Trace/ace_trace.h"
#include "drv_irq.h"
#include "log.h"

static drv_radio_cb_t m_radio_cb;
const drv_radio_packet_conf_t  m_radio_packet_conf = {
    // register 0
    .lflen = 1,                                 /* Length on air of LENGTH field in number of bits. */
    .s0len = 2,                                 /* Length on air of S0 field in number of bits. */
    .s1len = 6,                                 /* Length on air of S1 field in number of bits. */
    .s1incl = false,                            /* Include or exclude S1 field in RAM. */
    .plen = RADIO_PCNF0_PLEN_8bit ,           /* Length preamble on air. Decision point : TASK_START task */
    .crcinc = 0,                                /* Indicates if LENGTH field contains CRC or not */
    .termlen = 0,                               /* Length of TERM field in Long Range operation */
    // register 1
    .maxlen = 255,                                /* Maximum length of packet payload. */
    .startlen = 0,                              /* Static length in number of bytes */
    .balen = 3,                                 /* Base address length in number of bytes */
    .endian = false,                            /* On air endianness of packet. */
    .whiteen = true,                           /* Enable or disable packet whitening */
};

int channels[] = {37, 38, 39};
int freqs[] = {2, 26, 80};

unsigned char ble_adv_packet1[100] = {
    0x42,  
    0x1B,  //packet length 27 bytes (not including first 3 header bytes). 30 bytes total
    0x00,
    0x00,0x00,0x00,0x00,0x00,0x00,  //radio address 
    0x02, //Length of next data segment (1 data type byte + 1 byte data) = 2 bytes
    0x01, 0x06,  //AD type, advertise only flag 
    0x02, //next segment is 2 bytes...
    0x0A, 0x04, //Tx Power +4
    0x05, //5 bytes...
    0x16, 0x6E, 0x2A, 0x00, 0x00, //Temperature in celcius 00.00
    0x04, //4 bytes...
    0x16, 0x0f, 0x18, 0x00,  //Battery Level in percentage  
    0x03, //3 bytes...
    0x09, 0x48, 0x49  //short name, "HI"
};

static void drv_radio_irq_enable()
{
    uint8_t priority = 4;
    /* Check irq enable ? */
    if (!DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(NRF_RADIO)))
    {
        DRV_IRQ_PRIORITY_SET(DRV_IRQ_NUMBER_GET(NRF_RADIO), priority);
        DRV_IRQ_ENABLE(DRV_IRQ_NUMBER_GET(NRF_RADIO));
    }
}

static void drv_radio_irq_disable()
{
    /* Check irq enable ? */
    if (DRV_IRQ_IS_ENABLED(DRV_IRQ_NUMBER_GET(NRF_RADIO)))
    {
        DRV_IRQ_DISABLE(DRV_IRQ_NUMBER_GET(NRF_RADIO));
    }
}

drv_sta_t drv_radio_init(drv_radio_event_handler_t event_handler)
{
    if (m_radio_cb.drv_initialized == true)
    {
        return DRV_STA_NG;
    }

    m_radio_cb.event_handler = event_handler;
    m_radio_cb.drv_initialized = true;
    drv_radio_irq_enable();
    return DRV_STA_OK;
}

drv_sta_t drv_radio_reset()
{
    if (m_radio_cb.drv_initialized == false)
    {
        return DRV_STA_NG;
    }
    m_radio_cb.drv_initialized = false;
    drv_radio_irq_disable();
    return DRV_STA_OK;
}

drv_sta_t drv_radio_config()
{
    if (m_radio_cb.drv_initialized == false)
    {
        return DRV_STA_NG;
    }
    // Configure the radio here
    /* Radio power */
    hal_radio_power_set(true);
    // Configure radio with 2MBit Nordic proprietary mode
    hal_radio_mode_set(HAL_RADIO_MODE_NRF_1MBIT);
    // Configure packet radio
    hal_radio_packet_configure(&m_radio_packet_conf);
   
    // Configure address Prefix0 + Base0
    hal_radio_base0_set(0x89BED600);
    hal_radio_prefix0_set(0x8E);
    // Use logical address 0 (Prefix0 + Base0) for TX
    hal_radio_txaddress_set(0);
    // Initialize CRC (two bytes)
    hal_radio_crc_configure(3, HAL_RADIO_CRC_ADDR_SKIP, 0x00065B);
    hal_radio_crcinit_set(0x555555);
    // Enable fast rampup, new in nRF52
    hal_radio_modecnf0_set(true, RADIO_MODECNF0_DTX_B0);
    // 0dBm output power, sending packets at 2400MHz
    hal_radio_txpower_set(HAL_RADIO_TXPOWER_POS4DBM);
    // hal_radio_frequency_set(2400 + channel);
    // hal_radio_power_set(true);
    // Configure address of the packet and logic address to use
    hal_radio_packetptr_set(&ble_adv_packet1[0]);
    /* Configure shortcuts to start as soon as READY event is received, 
         and disable radio as soon as packet is sent.*/
    hal_radio_short_enable(HAL_RADIO_SHORT_READY_START_MASK | HAL_RADIO_SHORT_END_DISABLE_MASK);
    hal_radio_interrupt_enable(HAL_RADIO_INT_READY_MASK| 
                                HAL_RADIO_INT_END_MASK |
                                HAL_RADIO_INT_DISABLED_MASK);
    return DRV_STA_OK;
}

drv_sta_t drv_radio_send_data(uint8_t channel_index)
{
    /*  TX enable */
     // Initialize whitening value
    hal_radio_frequency_set(freqs[channel_index]);
    hal_radio_datawhiteiv_set(channels[channel_index]);
    hal_radio_event_clear(HAL_RADIO_EVENT_READY);
    hal_radio_task_trigger(HAL_RADIO_TASK_TXLEN);
    ace_trace_log("Send data %d \n", channel_index);
    return DRV_STA_OK;
}

drv_sta_t drv_radio_irq_handler()
{
    if(m_radio_cb.event_handler == NULL)
    {
        return DRV_STA_NG;
    }

    if (hal_radio_event_check(HAL_RADIO_EVENT_READY))
    {
        m_radio_cb.event_handler(DRV_RADIO_EVENT_READY);
        hal_radio_event_clear(HAL_RADIO_EVENT_READY);
        // hal_radio_task_trigger(HAL_RADIO_TASK_START);
    }
    if (hal_radio_event_check(HAL_RADIO_EVENT_END))
    {
        m_radio_cb.event_handler(DRV_RADIO_EVENT_END);
        hal_radio_event_clear(HAL_RADIO_EVENT_END);
        // hal_radio_task_trigger(HAL_RADIO_TASK_DISABLE);
    }
    if (hal_radio_event_check(HAL_RADIO_EVENT_DISABLED))
    {
        m_radio_cb.event_handler(DRV_RADIO_EVENT_DISABLED);
        hal_radio_event_clear(HAL_RADIO_EVENT_DISABLED);
    }

    return DRV_STA_OK;
}

