/********************************************************************************/
/*                Copyright (C) 2002-2009 Grape Systems, Inc.                   */
/*                     All Rights Reserved.                                     */
/*                                                                              */
/*  This software is furnished under a license and may be used and copied only  */
/*  in accordance with the terms of such license and with the inclusion of the  */
/*  above copyright notice. No title to and ownership of the software is        */
/*  transferred.                                                                */
/*  Grape Systems Inc. makes no warranties with respect to the performance of   */
/*  this computer program, and specifically disclaims any responsibility for    */
/*  any damages, special or consequential, connected with the use of this       */
/*  program.                                                                    */
/*                                                                              */
/********************************************************************************/

/********************************************************************************/
/*  acre_sem.c                                                                  */
/*  uITRON Library for ThreadX.(GR-TXi4)                                        */
/*                                                                              */
/*  Create semaphore(Auto ID)                                                   */
/*                                                                              */
/********************************************************************************/

#include "txi_knl.h"

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      acre_sem                                                                */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Create semaphore(ID number automatic assignment)                        */
/*                                                                              */
/* INPUT                                                                        */
/*      pk_csem             Pointer to the packet containing the semaphore      */
/*                          creation information.                               */
/*                                                                              */
/* OUTPUT                                                                       */
/*      E_PAR               Parameter error                                     */
/*      E_RSATR             Reserved attribute error                            */
/*      E_NOID              No ID number available                              */
/*      E_NOMEM             Insufficient memory                                 */
/*      E_CTX               Context error                                       */
/*      E_OK                Normal completion                                   */
/*                                                                              */
/* CALLS                                                                        */
/*      _kernel_object_find         Find free object index                      */
/*      __cre_sem                   Create semaphore                            */
/*                                  (Internal function).                        */
/*                                                                              */
/* CALLED BY                                                                    */
/*      Application                                                             */
/*                                                                              */
/* ALLOWED FROM                                                                 */
/*      Initialization                                                          */
/*      Task context                                                            */
/*                                                                              */
/* RELEASE HISTORY                                                              */
/*                                                                              */
/*  DATE            NAME                    DESCRIPTION                         */
/*                                                                              */
/*  2006/08/31      M. Miyashita    Initial version 2.0                         */
/*  2007/03/05      M. Miyashita    version 2.1, Modified comment(s).           */
/*  2009/07/10      M. Miyashita    version 2.2, Modified comment(s),           */
/*                                  The preemption control method was arranged. */
/*                                                                              */
/********************************************************************************/
ER_ID acre_sem(T_CSEM* pk_csem)
{
    ID semid;
    ER_ID rtn;
TX_INTERRUPT_SAVE_AREA

    CHECK_PARAM(pk_csem!=NULL && 0<pk_csem->maxsem && pk_csem->maxsem<=TMAX_MAXSEM &&
                pk_csem->isemcnt<=pk_csem->maxsem)
    CHECK_ATR(pk_csem->sematr, TA_TPRI|TA_TFIFO)
    CHECK_TSK_INIT_CONTEXT()

    TX_DISABLE  /* Lockout interrupts. */
    _tx_thread_preempt_disable++;   /* Disable preemption. */
    TX_RESTORE  /* Restore interrupts. */

    if((semid=_kernel_object_find(_kernel_sem_id, _kernel_sem_maxid))!=0)
    {
        if((rtn=(ER_ID)__cre_sem(semid, pk_csem))==E_OK)
        {
            rtn = (ER_ID)semid;
        }
    }
    else
    {
        rtn = (ER_ID)E_NOID;    /* No ID number available. */
    }

    TX_DISABLE  /* Lockout interrupts. */
    _tx_thread_preempt_disable--;   /* Release preemption. */
    TX_RESTORE  /* Restore interrupts. */

    return rtn;
}

