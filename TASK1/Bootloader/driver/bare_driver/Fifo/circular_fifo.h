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
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define BUFFER_SIZE 128

typedef struct circular_fifo_s circular_fifo;

struct circular_fifo_s
{
    /* data */
    uint8_t next;
    uint8_t first;
    uint8_t Buffer[BUFFER_SIZE + 1]; /* It needs 1 extra byte to difference full and empty */
    /* function */
    uint8_t (*isFull)(circular_fifo *self);
    uint8_t (*isEmpty)(circular_fifo *self);
    uint8_t (*getElement)(circular_fifo *self);
    uint8_t (*addElement)(circular_fifo *self, uint8_t data);
    uint8_t (*getNumOfElement)(circular_fifo *self);

};




#ifdef __cplusplus
}
#endif
#endif


