/******************************************************************************/
/*! @addtogroup Group2
    @file       circular_fifo.h
    @brief      
    @date       2024/06/28
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/

#ifndef _CIRCULAR_FIFO_H_
#define _CIRCULAR_FIFO_H_
#ifdef __cplusplus
extern "C"
{
#endif

/* CODE */
#include <stdint.h>

typedef struct circular_fifo_s circular_fifo;

struct circular_fifo_s
{
    /* data */

    /* function */
    uint8_t (*isFull)(void);
    uint8_t (*isEmpty)(void);
    uint8_t (*getElement)(void);
    uint8_t (*addElement)(uint8_t data);
    uint8_t (*getNumOfElement)(void);

};




#ifdef __cplusplus
}
#endif
#endif


