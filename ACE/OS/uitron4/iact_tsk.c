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
/*  iact_tsk.c                                                                  */
/*  uITRON Library for ThreadX.(GR-TXi4)                                        */
/*                                                                              */
/*  Activate task from non-task contexts                                        */
/*                                                                              */
/********************************************************************************/

#include "txi_knl.h"

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      iact_tsk                                                                */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Activate task from non-task contexts.                                   */
/*                                                                              */
/* INPUT                                                                        */
/*      tskid               ID number of the task.                              */
/*                                                                              */
/* OUTPUT                                                                       */
/*      E_ID                Invalid ID number                                   */
/*      E_CTX               Context error                                       */
/*      E_NOMEM             Insufficient memory                                 */
/*      E_QOVR              Queue overflow                                      */
/*      E_NOEXS             Non-existent object                                 */
/*      E_OK                Normal completion                                   */
/*                                                                              */
/* CALLS                                                                        */
/*      _kernel_task_tcb            Get tcb pointer                             */
/*      _kernel_system_request      Processing is required of system thread     */
/*                                                                              */
/* CALLED BY                                                                    */
/*      Application                                                             */
/*                                                                              */
/* ALLOWED FROM                                                                 */
/*      Non-task context                                                        */
/*                                                                              */
/* RELEASE HISTORY                                                              */
/*                                                                              */
/*  DATE            NAME                    DESCRIPTION                         */
/*                                                                              */
/*  2006/08/31      M. Miyashita    Initial version 2.0                         */
/*  2007/03/05      M. Miyashita    version 2.1, Modified comment(s).           */
/*  2009/07/10      M. Miyashita    version 2.2, Modified comment(s).           */
/*                                                                              */
/********************************************************************************/
ER iact_tsk(ID tskid)
{
    ER rtn = E_OK;
    _KERNEL_UITRON_TSK* pTcb;
TX_INTERRUPT_SAVE_AREA

    CHECK_ID(1, _kernel_tsk_maxid, tskid)
    CHECK_NOT_TSK_CONTEXT()

    TX_DISABLE  /* Lockout interrupts. */
    pTcb = _kernel_task_tcb(tskid);
    if(pTcb!=NULL)
    {
        if(pTcb->tskstat==TTS_DMT)
        {
            /* Restart this task */
            _kernel_system_request(_kernel_system_task_restart, pTcb);
        }
        else
        {
            if(pTcb->actcnt<TMAX_ACTCNT)
            {
                pTcb->actcnt++;
            }
            else
            {
                rtn = E_QOVR;   /* Overflow of activation queue. */
            }
        }
    }
    else
    {
        rtn = E_NOEXS;  /* The object is not registered. */
    }
    TX_RESTORE  /* Restore interrupts. */

    return rtn;
}

