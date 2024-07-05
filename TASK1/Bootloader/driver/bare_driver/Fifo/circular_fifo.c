/******************************************************************************/
/*! @addtogroup Group2
    @file       circular_fifo.c
    @brief      
    @date       2024/06/28
    @author     Development Dept at Tokyo (nguyen-thanh-tung@jcm-hq.co.jp)
    @par        Revision
    $Id$
    @par        Copyright (C)
    Japan CashMachine Co, Limited. All rights reserved.
******************************************************************************/


#include "circular_fifo.h"

uint8_t circular_getNumOfElement(circular_fifo *self);


void circular_fifo_init(circular_fifo *self,
                        uint8_t (*isFull)(circular_fifo *self),
                        uint8_t (*isEmpty)(circular_fifo *self),
                        uint8_t (*getElement)(circular_fifo *self),
                        uint8_t (*addElement)(circular_fifo *self, uint8_t data),
                        uint8_t (*getNumOfElement)(circular_fifo *self))
{
    self->isFull = isFull;
    self->isEmpty = isEmpty;
    self->getElement = getElement;
    self->addElement = addElement;
    self->getNumOfElement = getNumOfElement;

    self->first = 0;
    self->next = 0;

}


void circular_fifo_deinit(circular_fifo *self)
{

}

uint8_t circular_isFull(circular_fifo *self)
{
    if (circular_getNumOfElement(self) == BUFFER_SIZE)
    {
        return 1; /* TRUE */
    }
    else
    {
        return 0; /* FALSE */
    }
}

uint8_t circular_isEmpty(circular_fifo *self)
{
    if (self->next == self->first)
    {
        return 1; /* TRUE */
    }
    else
    {
        return 0; /* FALSE */
    }
}

uint8_t circular_getElement(circular_fifo *self)
{
    uint8_t theElement = 0;

    if (!circular_isEmpty(self))
    {
        theElement = self->Buffer[self->first];
        if (self->first != BUFFER_SIZE)
        {
            self->first ++;
        }
        else
        {
            self->first = 0;
        }
    }
    return theElement;
}

uint8_t circular_addElement(circular_fifo *self, uint8_t data)
{
    if (self->isFull(self))
    {
        self->Buffer[self->next] = data;
        if (self->next != BUFFER_SIZE)
        {
            self->next++;
        }
        else
        {
            self->next = 0;
        }
        return 1; /* TRUE */
    }
    else
    {
        return 0; /* FALSE */
    }
}

uint8_t circular_getNumOfElement(circular_fifo *self)
{
    if (self->next >= self->first)
    {
        return (self->next - self->first);
    }
    else
    {
        return (BUFFER_SIZE - self->next + self->first);
    }
}

circular_fifo *circular_fifo_create()
{
    circular_fifo *self = (circular_fifo*)malloc(sizeof(circular_fifo));
    if (self == NULL)
    {
        return NULL;
    }

    circular_fifo_init(self,
                        circular_isFull,
                        circular_isEmpty,
                        circular_getElement,
                        circular_addElement,
                        circular_getNumOfElement);

    return self;
}


