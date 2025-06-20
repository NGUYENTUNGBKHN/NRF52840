/********************************************************************************/
/*                Copyright (C) 2002-2016 Grape Systems, Inc.                   */
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
/*  trcv_dtq.c                                                                  */
/*  uITRON Library for ThreadX.(GR-TXi4)                                        */
/*                                                                              */
/*  Receive data queue with timeout                                             */
/*                                                                              */
/********************************************************************************/

#include "txi_knl.h"

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      __trcv_dtq                                                              */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Receive data queue(Internal function).                                  */
/*                                                                              */
/* INPUT                                                                        */
/*      dtqid               ID number of the data queue.                        */
/*      p_data              Data element receive from data queue                */
/*      tmout               Timeout value                                       */
/*                                                                              */
/* OUTPUT                                                                       */
/*      E_ID                Invalid ID number                                   */
/*      E_PAR               Parameter error                                     */
/*      E_CTX               Context error                                       */
/*      E_TMOUT             Timeout error                                       */
/*      E_RLWAI             Forced release from waiting                         */
/*      E_NOEXS             Non-existent object                                 */
/*      E_OK                Normal completion                                   */
/*                                                                              */
/* CALLS                                                                        */
/*      _kernel_resume_task         Resume a task with error code               */
/*      _kernel_thread_to_task      Get tcb pointer from thread control block   */
/*      _kernel_suspend_by_api      Suspend task for API                        */
/*                                                                              */
/* CALLED BY                                                                    */
/*      rcv_dtq                                                                 */
/*      prcv_dtq                                                                */
/*      trcv_dtq                                                                */
/*                                                                              */
/* ALLOWED FROM                                                                 */
/*      Internal                                                                */
/*                                                                              */
/* RELEASE HISTORY                                                              */
/*                                                                              */
/*  DATE            NAME                    DESCRIPTION                         */
/*                                                                              */
/*  2006/08/31      M. Miyashita    Initial version 2.0                         */
/*  2007/03/05      M. Miyashita    version 2.1, Modified comment(s).           */
/*  2009/07/10      M. Miyashita    version 2.2, Modified comment(s),           */
/*                                  The preemption control method was arranged. */
/*  2010/01/26      M. Miyashita    version 2.2a, Modified comment(s),          */
/*                                  A means to go into a waiting state was      */
/*                                  changed into the form which uses ThreadX API*/
/*                                  directly.                                   */
/*  2016/04/12      T. Shibuya      version 2.2n, Modified comment(s),          */
/*                                  Add a branch process of switching the       */
/*                                  waiting way depending on the                */
/*                                  pDtq->cdtq.dtqatr.                          */
/*                                  When they release the waiting waiting for   */
/*                                  transmission of the task, adding a process  */
/*                                  to clear the pTcb->wait_pri.                */
/*                                                                              */
/********************************************************************************/
ER __trcv_dtq(ID dtqid, VP_INT* p_data, TMO tmout)
{
    ER rtn = E_OK;
    _KERNEL_UITRON_DTQ* pDtq;
    _KERNEL_UITRON_TSK* pTcb;
TX_INTERRUPT_SAVE_AREA

    TX_DISABLE  /* Lockout interrupts. */
    pDtq = (_KERNEL_UITRON_DTQ*)ID_LIST(_kernel_dtq_id, dtqid);
    if(pDtq!=NULL)
    {
        if(pDtq->stsk!=NULL)
        {
            /* Remove from waiting list */
            pTcb = (_KERNEL_UITRON_TSK*)pDtq->stsk->data;
            _kernel_deque(&pTcb->wait);

            *p_data = (VP_INT)pTcb->waitdata;

            pTcb->wait_rtn = E_OK;
            pTcb->wait_obj = NULL;
            pTcb->wait_pri = NULL;

            /* Clear cleanup routine pointer. */
            pTcb->thread.tx_thread_suspend_cleanup = TX_NULL;

            if(pTcb->tskstat==TTS_WAS)
            {
                pTcb->wobjid = 0;
                pTcb->tskwait = TTW_NONE;
                pTcb->tskstat = TTS_SUS;
            }
            else
            {
                pTcb->wobjid = 0;
                pTcb->tskwait = TTW_NONE;
                pTcb->tskstat = TTS_RDY;

                _tx_thread_preempt_disable++;   /* Temporarily disable preemption. */
                TX_RESTORE  /* Restore interrupts. */
                _tx_thread_system_resume(&pTcb->thread);
                TX_DISABLE  /* Lockout interrupts. */
            }
        }
        else
        {
            if(0<pDtq->dtqcnt)
            {
                /* Get data to queue. */
                *p_data = pDtq->dtqptr[pDtq->getpos];
                pDtq->dtqcnt--;
                pDtq->getpos = (pDtq->getpos+1)%pDtq->cdtq.dtqcnt;
            }
            else
            {
                if(tmout!=TMO_POL)
                {
                    pTcb = _kernel_thread_to_task(_tx_thread_current_ptr);
                    if(pTcb!=NULL && DISPATCH_ENABLE)
                    {
                        /* Wait for data queue. */
                        if(pDtq->cdtq.dtqatr==TA_TFIFO)
                        {
                            _kernel_enque(&pDtq->rtsk, &pTcb->wait);
                        }
                        else
                        {
                            _kernel_enque_task_pri(&pDtq->rtsk, &pTcb->wait);
                        }

                        pTcb->tskstat = TTS_WAI;
                        pTcb->tskwait = TTW_RDTQ;
                        pTcb->wobjid = dtqid;
                        pTcb->wait_obj = pDtq;
                        pTcb->wait_pri = (pDtq->cdtq.dtqatr!=TA_TFIFO);

                        pTcb->waitdata = p_data;

                        pTcb->wait_rtn = E_OK;

                        /* Setup cleanup routine pointer.  */
                        pTcb->thread.tx_thread_suspend_cleanup = _kernel_task_cleanup;

                        /* Set the state to suspended.  */
                        pTcb->thread.tx_thread_state = TX_SUSPENDED;

                        /* Set the suspending flag.  */
                        pTcb->thread.tx_thread_suspending =  TX_TRUE;

                        /* Setup the timeout period.  */
                        if(tmout==TMO_FEVR)
                        {
                            pTcb->thread.tx_thread_timer.tx_timer_internal_remaining_ticks = TX_WAIT_FOREVER;
                        }
                        else
                        {
                            if(0<TIM2TIC(tmout))
                            {
                                pTcb->thread.tx_thread_timer.tx_timer_internal_remaining_ticks = TIM2TIC(tmout);
                            }
                            else
                            {
                                pTcb->thread.tx_thread_timer.tx_timer_internal_remaining_ticks = 1;
                            }
                        }

                        _tx_thread_preempt_disable++;   /* Temporarily disable preemption.  */
                        TX_RESTORE  /* Restore interrupts. */

                        _tx_thread_system_suspend(&pTcb->thread);

                        TX_DISABLE  /* Lockout interrupts. */
                        rtn = pTcb->wait_rtn;
                    }
                    else
                    {
                        rtn = E_CTX;    /* No support contexts. */
                    }
                }
                else
                {
                    rtn = E_TMOUT;
                }
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

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      trcv_dtq                                                                */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Receive data queue with timeout.                                        */
/*                                                                              */
/* INPUT                                                                        */
/*      dtqid               ID number of the data queue.                        */
/*      p_data              Data element receive from data queue                */
/*      tmout               Timeout value                                       */
/*                                                                              */
/* OUTPUT                                                                       */
/*      E_ID                Invalid ID number                                   */
/*      E_PAR               Parameter error                                     */
/*      E_CTX               Context error                                       */
/*      E_TMOUT             Timeout error                                       */
/*      E_RLWAI             Forced release from waiting                         */
/*      E_NOEXS             Non-existent object                                 */
/*      E_OK                Normal completion                                   */
/*                                                                              */
/* CALLS                                                                        */
/*      __trcv_dtq                  Receive data queue(Internal function)       */
/*                                                                              */
/* CALLED BY                                                                    */
/*      Application                                                             */
/*                                                                              */
/* ALLOWED FROM                                                                 */
/*      Task context                                                            */
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
ER trcv_dtq(ID dtqid, VP_INT* p_data, TMO tmout)
{
    CHECK_ID(1, _kernel_dtq_maxid, dtqid)
    CHECK_PARAM(p_data!=NULL)
    CHECK_TMOUT(tmout)
    CHECK_TSK_CONTEXT()

    return __trcv_dtq(dtqid, p_data, tmout);
}

