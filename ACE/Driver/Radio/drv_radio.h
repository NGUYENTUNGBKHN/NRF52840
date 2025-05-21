/******************************************************************************/
/*! @addtogroup Group2
    @file       drv_radio.h
    @brief      
    @date       2025/05/13
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _DRV_RADIO_H_
#define _DRV_RADIO_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include "drv_common.h"
// #include "drv_irq.h"
#include "hal_radio.h"

typedef enum DRV_RADIO_EVENT_S
{
    DRV_RADIO_EVENT_READY       = 0,    /*!< READY event */
    DRV_RADIO_EVENT_ADDRESS     = 1,    /*!< ADDRESS event */
    DRV_RADIO_EVENT_PAYLOAD     = 2,    /*!< PAYLOAD event */
    DRV_RADIO_EVENT_END         = 3,    /*!< END event */
    DRV_RADIO_EVENT_DISABLED    = 4,    /*!< DISABLED event */
    DRV_RADIO_EVENT_DEVMATCH    = 5,    /*!< DEVMATCH event */
    DRV_RADIO_EVENT_DEVMISS     = 6,    /*!< DEVMISS event */
    DRV_RADIO_EVENT_RSSIEND     = 7,    /*!< RSSIEND event */
    DRV_RADIO_EVENT_BCMATCH     = 8,    /*!< BCMATCH event */
    DRV_RADIO_EVENT_CRCOK       = 9,    /*!< CRCOK event */
    DRV_RADIO_EVENT_CRCERROR    = 10,   /*!< CRCERROR event */
    DRV_RADIO_EVENT_FRAMESTART  = 11,   /*!< FRAMESTART event */
    DRV_RADIO_EVENT_ENEND       = 12,   /*!< ENDED event */
    DRV_RADIO_EVENT_EDSTOPPED   = 13,   /*!< EDSTOPPED event */
    DRV_RADIO_EVENT_CCAIDLE     = 14,   /*!< CCAIDLE event */
    DRV_RADIO_EVENT_CCABUSY     = 15,   /*!< CCABUSY event */
    DRV_RADIO_EVENT_CCASTOPPED  = 16,   /*!< CCASTOPPED event */
    DRV_RADIO_EVENT_RATEBOOST   = 17,   /*!< RATEBOOST event */
    DRV_RADIO_EVENT_TXREADY     = 18,   /*!< TXREADY event */
    DRV_RADIO_EVENT_RXREADY     = 19,   /*!< RXREADY event */
    DRV_RADIO_EVENT_MHRMATCH    = 20,   /*!< MHRMATCH event */
    DRV_RADIO_EVENT_SYNC        = 21,   /*!< SYNC event */
    DRV_RADIO_EVENT_PHYEND      = 22,   /*!< PHYEND event */
}drv_radio_event_t;

typedef void (*drv_radio_event_handler_t)(drv_radio_event_t event);

typedef struct DRV_RADIO_CB_S
{
    drv_radio_event_handler_t event_handler; /*!< Event handler */
    bool                     drv_initialized; /*!< Driver initialized */
}drv_radio_cb_t;

// typedef struct drv_radio_packet_conf_t;
#define drv_radio_packet_conf_t hal_radio_packet_conf_t

extern drv_sta_t drv_radio_init(drv_radio_event_handler_t event_handler);
extern drv_sta_t drv_radio_config();
extern drv_sta_t drv_radio_send_data(uint8_t channel_index);
// extern drv_sta_t drv_radio_set_packet(hal_radio_packet_conf_t *packet_conf);


#ifdef __cplusplus
}
#endif
#endif
