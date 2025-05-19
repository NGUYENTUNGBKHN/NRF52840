/******************************************************************************/
/*! @addtogroup Group2
    @file       hal_radio.h
    @brief      
    @date       2025/05/01
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/
#ifndef _HAL_RADIO_H_
#define _HAL_RADIO_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "hal_common.h"

/**
 * @brief   Radio task.
 * @details Radio task to start/stop radio.
 */
typedef enum
{
    HAL_RADIO_TASK_TXLEN        = offsetof(NRF_RADIO_Type, TASKS_TXEN),         /*!< TXEN task */
    HAL_RADIO_TASK_RXEN         = offsetof(NRF_RADIO_Type, TASKS_RXEN),         /*!< RXEN task */
    HAL_RADIO_TASK_START        = offsetof(NRF_RADIO_Type, TASKS_START),        /*!< START task */
    HAL_RADIO_TASK_STOP         = offsetof(NRF_RADIO_Type, TASKS_STOP),         /*!< STOP task */
    HAL_RADIO_TASK_DISABLE      = offsetof(NRF_RADIO_Type, TASKS_DISABLE),      /*!< DISABLE task */
    HAL_RADIO_TASK_RSSISTART    = offsetof(NRF_RADIO_Type, TASKS_RSSISTART),    /*!< RSSISTART task */
    HAL_RADIO_TASK_RSSISTOP     = offsetof(NRF_RADIO_Type, TASKS_RSSISTOP),     /*!< RSSISTOP task */
    HAL_RADIO_TASK_BCSTART      = offsetof(NRF_RADIO_Type, TASKS_BCSTART),      /*!< BCSTART task */
    HAL_RADIO_TASK_BCSTOP       = offsetof(NRF_RADIO_Type, TASKS_BCSTOP),       /*!< BCSTOP task */
    HAL_RADIO_TASK_EDSTART      = offsetof(NRF_RADIO_Type, TASKS_EDSTART),      /*!< EDSTART task */
    HAL_RADIO_TASK_EDSTOP       = offsetof(NRF_RADIO_Type, TASKS_EDSTOP),       /*!< EDSTOP task */
    HAL_RADIO_TASK_CCASTART     = offsetof(NRF_RADIO_Type, TASKS_CCASTART),     /*!< CCASTART task */
    HAL_RADIO_TASK_CCASTOP      = offsetof(NRF_RADIO_Type, TASKS_CCASTOP)       /*!< CCASTOP task */
}hal_radio_task_t;


/**
 * @brief   Event.
 * @details Event to indicate that a task has been started or stopped.
 */
typedef enum
{
    HAL_RADIO_EVENT_READY       = offsetof(NRF_RADIO_Type, EVENTS_READY),       /*!< READY event */
    HAL_RADIO_EVENT_ADDRESS     = offsetof(NRF_RADIO_Type, EVENTS_ADDRESS),     /*!< ADDRESS event */
    HAL_RADIO_EVENT_PAYLOAD     = offsetof(NRF_RADIO_Type, EVENTS_PAYLOAD),     /*!< PAYLOAD event */
    HAL_RADIO_EVENT_END         = offsetof(NRF_RADIO_Type, EVENTS_END),         /*!< END event */
    HAL_RADIO_EVENT_DISABLED    = offsetof(NRF_RADIO_Type, EVENTS_DISABLED),    /*!< DISABLED event */
    HAL_RADIO_EVENT_DEVMATCH    = offsetof(NRF_RADIO_Type, EVENTS_DEVMATCH),    /*!< DEVMATCH event */
    HAL_RADIO_EVENT_DEVMISS     = offsetof(NRF_RADIO_Type, EVENTS_DEVMISS),     /*!< DEVMISS event */
    HAL_RADIO_EVENT_RSSIEND     = offsetof(NRF_RADIO_Type, EVENTS_RSSIEND),     /*!< RSSIEND event */
    HAL_RADIO_EVENT_BCMATCH     = offsetof(NRF_RADIO_Type, EVENTS_BCMATCH),     /*!< BCMATCH event */
    HAL_RADIO_EVENT_CRCOK       = offsetof(NRF_RADIO_Type, EVENTS_CRCOK),       /*!< CRCOK event */
    HAL_RADIO_EVENT_CRCERROR    = offsetof(NRF_RADIO_Type, EVENTS_CRCERROR),    /*!< CRCERROR event */
    HAL_RADIO_EVENT_FRAMESTART  = offsetof(NRF_RADIO_Type, EVENTS_FRAMESTART),  /*!< FRAMESTART event */
    HAL_RADIO_EVENT_ENEND       = offsetof(NRF_RADIO_Type, EVENTS_EDEND),       /*!< END event */
    HAL_RADIO_EVENT_EDSTOPPED   = offsetof(NRF_RADIO_Type, EVENTS_EDSTOPPED),   /*!< EDSTOPPED event */
    HAL_RADIO_EVENT_CCAIDLE     = offsetof(NRF_RADIO_Type, EVENTS_CCAIDLE),     /*!< CCAIDLE event */
    HAL_RADIO_EVENT_CCABUSY     = offsetof(NRF_RADIO_Type, EVENTS_CCABUSY),     /*!< CCABUSY event */
    HAL_RADIO_EVENT_CCASTOPPED  = offsetof(NRF_RADIO_Type, EVENTS_CCASTOPPED),  /*!< CCASTOPPED event */
    HAL_RADIO_EVENT_RATEBOOST   = offsetof(NRF_RADIO_Type, EVENTS_RATEBOOST),   /*!< RATEBOOST event */
    HAL_RADIO_EVENT_TXREADY     = offsetof(NRF_RADIO_Type, EVENTS_TXREADY),     /*!< TXREADY event */
    HAL_RADIO_EVENT_RXREADY     = offsetof(NRF_RADIO_Type, EVENTS_RXREADY),     /*!< RXREADY event */
    HAL_RADIO_EVENT_MHRMATCH    = offsetof(NRF_RADIO_Type, EVENTS_MHRMATCH),    /*!< MHRMATCH event */
    HAL_RADIO_EVENT_SYNC        = offsetof(NRF_RADIO_Type, EVENTS_SYNC),        /*!< SYNC event */
    HAL_RADIO_EVENT_PHYEND      = offsetof(NRF_RADIO_Type, EVENTS_PHYEND),      /*!< PHYEND event */
}hal_radio_event_t;

/**
 * @brief   Radio interrupt.
 * @details Radio interrupt to indicate that a task has been started or stopped.
 */
typedef enum
{
    HAL_RADIO_INT_READY_MASK        = RADIO_INTENSET_READY_Msk,         /*!< READY event */
    HAL_RADIO_INT_ADDRESS_MASK      = RADIO_INTENSET_ADDRESS_Msk,       /*!< ADDRESS event */
    HAL_RADIO_INT_PAYLOAD_MASK      = RADIO_INTENSET_PAYLOAD_Msk,       /*!< PAYLOAD event */
    HAL_RADIO_INT_END_MASK          = RADIO_INTENSET_END_Msk,           /*!< END event */
    HAL_RADIO_INT_DISABLED_MASK     = RADIO_INTENSET_DISABLED_Msk,      /*!< DISABLED event */
    HAL_RADIO_INT_DEVMATCH_MASK     = RADIO_INTENSET_DEVMATCH_Msk,      /*!< DEVMATCH event */
    HAL_RADIO_INT_DEVMISS_MASK      = RADIO_INTENSET_DEVMISS_Msk,       /*!< DEVMISS event */
    HAL_RADIO_INT_RSSIEND_MASK      = RADIO_INTENSET_RSSIEND_Msk,       /*!< RSSIEND event */
    HAL_RADIO_INT_BCMATCH_MASK      = RADIO_INTENSET_BCMATCH_Msk,       /*!< BCMATCH event */
    HAL_RADIO_INT_CRCOK_MASK        = RADIO_INTENSET_CRCOK_Msk,         /*!< CRCOK event */
    HAL_RADIO_INT_CRCERROR_MASK     = RADIO_INTENSET_CRCERROR_Msk,      /*!< CRCERROR event */
    HAL_RADIO_INT_FRAMESTART_MASK   = RADIO_INTENSET_FRAMESTART_Msk,    /*!< FRAMESTART event */
    HAL_RADIO_INT_ENEND_MASK        = RADIO_INTENSET_EDEND_Msk,         /*!< ENDED event */
    HAL_RADIO_INT_EDSTOPPED_MASK    = RADIO_INTENSET_EDSTOPPED_Msk,     /*!< EDSTOPPED event */
    HAL_RADIO_INT_CCAIDLE_MASK      = RADIO_INTENSET_CCAIDLE_Msk,       /*!< CCAIDLE event */
    HAL_RADIO_INT_CCABUSY_MASK      = RADIO_INTENSET_CCABUSY_Msk,       /*!< CCABUSY event */
    HAL_RADIO_INT_CCASTOPPED_MASK   = RADIO_INTENSET_CCASTOPPED_Msk,    /*!< CCASTOPPED event */
    HAL_RADIO_INT_RATEBOOST_MASK    = RADIO_INTENSET_RATEBOOST_Msk,     /*!< RATEBOOST event */
    HAL_RADIO_INT_TXREADY_MASK      = RADIO_INTENSET_TXREADY_Msk,       /*!< TXREADY event */
    HAL_RADIO_INT_RXREADY_MASK      = RADIO_INTENSET_RXREADY_Msk,       /*!< RXREADY event */
    HAL_RADIO_INT_MHRMATCH_MASK     = RADIO_INTENSET_MHRMATCH_Msk,      /*!< MHRMATCH event */
    HAL_RADIO_INT_SYNC_MASK         = RADIO_INTENSET_SYNC_Msk,         /*!< SYNC event */
    HAL_RADIO_INT_PHYEND_MASK       = RADIO_INTENSET_PHYEND_Msk,        /*!< PHYEND event */
}hal_radio_interrupt_mask_t;

/**
 * @brief   Radio shortcut.
 * @details Radio shortcut to indicate that a task has been started or stopped.
 */
typedef enum
{
    HAL_RADIO_SHORT_READY_START_MASK        = RADIO_SHORTS_READY_START_Msk,         /*!< READY event to START task */
    HAL_RADIO_SHORT_END_DISABLE_MASK        = RADIO_SHORTS_END_DISABLE_Msk,         /*!< END event to DISABLE task */
    HAL_RADIO_SHORT_DISABLED_TXEN_MASK      = RADIO_SHORTS_DISABLED_TXEN_Msk,       /*!< DISABLED event to TXEN task */
    HAL_RADIO_SHORT_DISABLED_RXEN_MASK      = RADIO_SHORTS_DISABLED_RXEN_Msk,       /*!< DISABLED event to RXEN task */
    HAL_RADIO_SHORT_ADDRESS_RSSISTART_MASK  = RADIO_SHORTS_ADDRESS_RSSISTART_Msk,   /*!< ADDRESS event to RSSISTART task */
    HAL_RADIO_SHORT_END_START_MASK          = RADIO_SHORTS_END_START_Msk,           /*!< END event to START task */
    HAL_RADIO_SHORT_ADDRESS_BCSTART_MASK    = RADIO_SHORTS_ADDRESS_BCSTART_Msk,     /*!< ADDRESS event to BCSTART task */
    HAL_RADIO_SHORT_DISABLED_RSSISTOP_MASK  = RADIO_SHORTS_DISABLED_RSSISTOP_Msk,   /*!< DISABLED event to RSSISTOP task */
    HAL_RADIO_SHORT_RXREADY_CCASTART_MASK   = RADIO_SHORTS_RXREADY_CCASTART_Msk,    /*!< RXREADY event to CCASTART task */
    HAL_RADIO_SHORT_CCAIDLE_TXEN_MASK       = RADIO_SHORTS_CCAIDLE_TXEN_Msk,        /*!< CCAIDLE event to TXEN task */
    HAL_RADIO_SHORT_CCABUSY_DISABLE_MASK    = RADIO_SHORTS_CCABUSY_DISABLE_Msk,     /*!< CCABUSY event to DISABLE task */
    HAL_RADIO_SHORT_FRAMESTART_BCSTART_MASK = RADIO_SHORTS_FRAMESTART_BCSTART_Msk,  /*!< FRAMESTART event to BCSTART task */
    HAL_RADIO_SHORT_READY_EDSTART_MASK      = RADIO_SHORTS_READY_EDSTART_Msk,       /*!< READY event to EDSTART task */
    HAL_RADIO_SHORT_EDEND_DISABLE_MASK      = RADIO_SHORTS_EDEND_DISABLE_Msk,       /*!< EDEND event to DISABLE task */
    HAL_RADIO_SHORT_CCAIDLE_STOP_MASK       = RADIO_SHORTS_CCAIDLE_STOP_Msk,        /*!< CCAIDLE event to STOP task */
    HAL_RADIO_SHORT_TXREADY_START_MASK      = RADIO_SHORTS_TXREADY_START_Msk,       /*!< TXREADY event to START task */
    HAL_RADIO_SHORT_RXREADY_START_MASK      = RADIO_SHORTS_RXREADY_START_Msk,       /*!< RXREADY event to START task */
    HAL_RADIO_SHORT_PHYEND_DISABLE_MASK     = RADIO_SHORTS_PHYEND_DISABLE_Msk,      /*!< PHYEND event to DISABLE task */
    HAL_RADIO_SHORT_PHYEND_START_MASK       = RADIO_SHORTS_PHYEND_START_Msk,        /*!< PHYEND event to START task */
}hal_radio_shortcut_mask_t;

/**
 * @brief   Radio state.   
 * @details Radio state to indicate that a task has been started or stopped.
 */
typedef enum
{
    HAL_RADIO_STATE_DISABLED    = RADIO_STATE_STATE_Disabled,   /*!< Radio is disabled */
    HAL_RADIO_STATE_RXRU        = RADIO_STATE_STATE_RxRu,       /*!< Radio is in RXRU state */
    HAL_RADIO_STATE_RXIDLE      = RADIO_STATE_STATE_RxIdle,     /*!< Radio is in RXIDLE state */
    HAL_RADIO_STATE_RX          = RADIO_STATE_STATE_Rx,         /*!< Radio is in RX state */
    HAL_RADIO_STATE_RXDISABLE   = RADIO_STATE_STATE_RxDisable,  /*!< Radio is in RXDISABLE state */
    HAL_RADIO_STATT_TXRU        = RADIO_STATE_STATE_TxRu,       /*!< Radio is in TXRU state */
    HAL_RADIO_STATE_TXIDLE      = RADIO_STATE_STATE_TxIdle,     /*!< Radio is in TXIDLE state */
    HAL_RADIO_STATE_TX          = RADIO_STATE_STATE_Tx,         /*!< Radio is in TX state */
    HAL_RADIO_STATE_TXDISABLE   = RADIO_STATE_STATE_TxDisable,  /*!< Radio is in TXDISABLE state */
} hal_radio_state_t;

/**
 * @brief   Radio packet configuration.
 * @details Radio packet configuration.
 */
typedef struct HAL_RADIO_PACKET_S
{
    // registers 0
    uint8_t lflen;          /* Length on air of LENGTH field in number of bits. */
    uint8_t s0len;          /* Length on air of S0 field in number of bits. */
    uint8_t s1len;          /* Length on air of S1 field in number of bits. */
    bool s1incl;            /* Include or exclude S1 field in RAM. */
    uint8_t cilen;          /* Length of code indicator - long range */
    uint8_t plen;           /* Length preamble on air. Decision point : TASK_START task */
    uint8_t crcinc;         /* Indicates if LENGTH field contains CRC or not */
    uint8_t termlen;        /* Length of TERM field in Long Range operation */
    // registers 1
    uint8_t maxlen;         /* Maximum length of packet payload. */
    uint8_t startlen;       /* Static length in number of bytes */
    uint8_t balen;          /* Base address length in number of bytes */
    bool endian;            /* On air endianness of packet. */
    bool whiteen;           /* Enable or disable packet whitening */
}hal_radio_packet_conf_t;


/* TASK function */
__STATIC_INLINE void hal_radio_task_trigger(hal_radio_task_t task)
{
    *((volatile uint32_t *)((uint8_t *)NRF_RADIO + (uint32_t)task)) = 0x01UL;
}

__STATIC_INLINE uint32_t hal_radio_task_address_get(hal_radio_task_t task)
{
    return ((uint32_t)NRF_RADIO + (uint32_t)task);
}

/* Event function */
__STATIC_INLINE void hal_radio_event_clear(hal_radio_event_t event)
{
    *((volatile uint32_t *)((uint8_t *)NRF_RADIO + (uint32_t)event)) = 0x00UL;
}

__STATIC_INLINE uint32_t hal_radio_event_address_get(hal_radio_event_t event)
{
    return ((uint32_t)NRF_RADIO + (uint32_t)event);
}

/* Shortcut function */
__STATIC_INLINE void hal_radio_short_enable(hal_radio_shortcut_mask_t short_mask)
{
    NRF_RADIO->SHORTS |= short_mask;
}

__STATIC_INLINE void hal_radio_short_disable(hal_radio_shortcut_mask_t short_mask)
{
    NRF_RADIO->SHORTS &= ~short_mask;
}

__STATIC_INLINE void hal_radio_short_set(hal_radio_shortcut_mask_t short_mask)
{
    NRF_RADIO->SHORTS = short_mask;
}

__STATIC_INLINE uint32_t hal_radio_short_get(void)
{
    return NRF_RADIO->SHORTS;
}

/* Interrupt function */
__STATIC_INLINE void hal_radio_interrupt_enable(hal_radio_interrupt_mask_t int_mask)
{
    NRF_RADIO->INTENSET = int_mask;
}

__STATIC_INLINE void hal_radio_interrupt_disable(hal_radio_interrupt_mask_t int_mask)
{
    NRF_RADIO->INTENCLR = int_mask;
}

__STATIC_INLINE bool hal_radio_interrupt_enable_check(hal_radio_interrupt_mask_t int_mask)
{
    return (bool)(NRF_RADIO->INTENSET & int_mask);
}

/* Get Radio status */
__STATIC_INLINE bool hal_radio_crc_status_check()
{
    return ((NRF_RADIO->CRCSTATUS & RADIO_CRCSTATUS_CRCSTATUS_Msk) >> RADIO_CRCSTATUS_CRCSTATUS_Pos)
           == RADIO_CRCSTATUS_CRCSTATUS_CRCOk;
}

__STATIC_INLINE uint8_t hal_radio_rxmatch_get(void)
{
    return (uint8_t)(NRF_RADIO->RXMATCH );
}

__STATIC_INLINE uint32_t hal_radio_rxcrc_get(void)
{
    return (NRF_RADIO->RXCRC );
}

__STATIC_INLINE uint8_t hal_radio_dai_get(void)
{
    return (uint8_t)(NRF_RADIO->DAI );
}

__STATIC_INLINE bool hall_radio_pdustat_get()
{
    return (bool)(NRF_RADIO->PDUSTAT & RADIO_PDUSTAT_PDUSTAT_Msk);
}

__STATIC_INLINE uint8_t hal_radio_cistat_get(void)
{
    return (uint8_t)((NRF_RADIO->PDUSTAT & RADIO_PDUSTAT_CISTAT_Msk) >> RADIO_PDUSTAT_CISTAT_Pos);
}

__STATIC_INLINE void hal_radio_packetptr_set(const void * p_packet)
{
    NRF_RADIO->PACKETPTR = (uint32_t)p_packet;
}

__STATIC_INLINE void * hal_radio_packetptr_get(void)
{
    return (void *)NRF_RADIO->PACKETPTR;
}

__STATIC_INLINE void hal_radio_frequency_set(uint32_t frequency)
{
    if (frequency > 2500)
    {
        return;
    }
    uint32_t freq = 0;
    if (frequency < 2400)
    {
        freq = ((uint32_t)frequency - 2360) | (RADIO_FREQUENCY_MAP_Low << RADIO_FREQUENCY_MAP_Pos);
    }
    else
    {
        freq = ((uint32_t)frequency - 2400) | (RADIO_FREQUENCY_MAP_Default << RADIO_FREQUENCY_MAP_Pos);
    }

    NRF_RADIO->FREQUENCY = freq;
}

__STATIC_INLINE uint32_t hal_radio_frequency_get(void)
{
    uint32_t freq = 0;

    if (((NRF_RADIO->FREQUENCY & RADIO_FREQUENCY_MAP_Msk) >> RADIO_FREQUENCY_MAP_Pos) == RADIO_FREQUENCY_MAP_Low)
    {
        freq = 2360;
    }
    else
    {
        freq = 2360;
    }
    freq += (NRF_RADIO->FREQUENCY & RADIO_FREQUENCY_FREQUENCY_Msk) >> RADIO_FREQUENCY_FREQUENCY_Pos;

    return freq;
}

// __STATIC_INLINE void hal_radio_txpower_set(hal_radio_txpower_t tx_power)
// {
//     NRF_RADIO->TXPOWER = (((uint32_t)tx_power) << RADIO_TXPOWER_TXPOWER_Pos);
// }

// __STATIC_INLINE hal_radio_txpower_t nrf_radio_txpower_get(void)
// {
//     return (hal_radio_txpower_t)(NRF_RADIO->TXPOWER >> RADIO_TXPOWER_TXPOWER_Pos);
// }

// __STATIC_INLINE void hal_radio_mode_set(hal_radio_mode_t radio_mode)
// {
//     NRF_RADIO->MODE = ((uint32_t) radio_mode << RADIO_MODE_MODE_Pos);
// }

// __STATIC_INLINE hal_radio_mode_t hal_radio_mode_get(void)
// {
//     return (hal_radio_mode_t)((NRF_RADIO->MODE & RADIO_MODE_MODE_Msk) >> RADIO_MODE_MODE_Pos);
// }

__STATIC_INLINE void hal_radio_packet_configure(const hal_radio_packet_conf_t * p_packet_conf)
{
    NRF_RADIO->PCNF0 = ((uint32_t)p_packet_conf->lflen << RADIO_PCNF0_LFLEN_Pos) |      // Length on air of LENGTH field in number of bits.
                        ((uint32_t)p_packet_conf->s0len << RADIO_PCNF0_S0LEN_Pos) |     // Length on air of S0 field in number of bits.
                        ((uint32_t)p_packet_conf->s1len << RADIO_PCNF0_S1LEN_Pos) |     // Length on air of S1 field in number of bits.
                        (p_packet_conf->s1incl ?
                            (RADIO_PCNF0_S1INCL_Include << RADIO_PCNF0_S1INCL_Pos):
                            (RADIO_PCNF0_S1INCL_Automatic << RADIO_PCNF0_S1INCL_Pos)) |   
                        ((uint32_t)p_packet_conf->plen << RADIO_PCNF0_PLEN_Pos) |
                        (p_packet_conf->crcinc ?
                            (RADIO_PCNF0_CRCINC_Include << RADIO_PCNF0_CRCINC_Pos):
                            (RADIO_PCNF0_CRCINC_Exclude << RADIO_PCNF0_CRCINC_Pos)) |
                        ((uint32_t)p_packet_conf->termlen << RADIO_PCNF0_TERMLEN_Pos);

    NRF_RADIO->PCNF1 = ((uint32_t)p_packet_conf->maxlen << RADIO_PCNF1_MAXLEN_Pos) |        // Maximum length of packet payload.
                        ((uint32_t)p_packet_conf->startlen << RADIO_PCNF1_STATLEN_Pos) |    // Static length in number of bytes
                        ((uint32_t)p_packet_conf->balen << RADIO_PCNF1_BALEN_Pos) |         // Base address length in number of bytes.
                        (p_packet_conf->endian ?
                            (RADIO_PCNF1_ENDIAN_Big << RADIO_PCNF1_ENDIAN_Pos):
                            (RADIO_PCNF1_ENDIAN_Little << RADIO_PCNF1_ENDIAN_Pos)) |
                        (p_packet_conf->whiteen ?
                            (RADIO_PCNF1_WHITEEN_Enabled << RADIO_PCNF1_WHITEEN_Pos):
                            (RADIO_PCNF1_WHITEEN_Disabled << RADIO_PCNF1_WHITEEN_Pos));

}


#ifdef __cplusplus
}
#endif
#endif

