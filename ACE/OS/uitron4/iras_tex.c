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
/*  iras_tex.c                                                                  */
/*  uITRON Library for ThreadX.(GR-TXi4)                                        */
/*                                                                              */
/*  Raise task exception from non-task contexts                                 */
/*                                                                              */
/********************************************************************************/

#include "txi_knl.h"

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      iras_tex                                                                */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Raise task exception from non-task contexts.                            */
/*                                                                              */
/* INPUT                                                                        */
/*      tskid               ID number of the task.                              */
/*      rasptn              Raise patern data.                                  */
/*                                                                              */
/* OUTPUT                                                                       */
/*      E_ID                Invalid ID number                                   */
/*      E_PAR               Parameter error                                     */
/*      E_CTX               Context error                                       */
/*      E_NOEXS             Non-existent object                                 */
/*      E_OK                Normal completion                                   */
/*                                                                              */
/* CALLS                                                                        */
/*      _kernel_task_exception_set  Set task exception information              */
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
ER iras_tex(ID tskid, TEXPTN rasptn)
{
    ER rtn = E_OK;
    _KERNEL_UITRON_TSK* pTcb;
TX_INTERRUPT_SAVE_AREA

    CHECK_ID(1, _kernel_tsk_maxid, tskid)
    CHECK_PARAM(rasptn!=0)
    CHECK_NOT_TSK_CONTEXT()

    TX_DISABLE  /* Lockout interrupts. */
    pTcb = _kernel_task_tcb(tskid);
    if(pTcb!=NULL)
    {
        if(pTcb->texrtn!=NULL && pTcb->tskstat!=TTS_DMT)
        {
            pTcb->rasptn |= rasptn;

            if((pTcb->texstat&TTEX_DISABLE_BIT)==0)
            {
                _kernel_task_exception_set(pTcb);
            }
        }
        else
        {
            rtn = E_OBJ;    /* Object error */
        }
    }
    else
    {
        rtn = E_NOEXS;  /* The object is not registered. */
    }
    TX_RESTORE  /* Restore interrupts. */

    return rtn;
}

