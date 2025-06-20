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
/*  sus_tsk.c                                                                   */
/*  uITRON Library for ThreadX.(GR-TXi4)                                        */
/*                                                                              */
/*  Suspend task                                                                */
/*                                                                              */
/********************************************************************************/

#include "txi_knl.h"

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      sus_tsk                                                                 */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Suspend task.                                                           */
/*                                                                              */
/* INPUT                                                                        */
/*      tskid               ID number of the task.                              */
/*                                                                              */
/* OUTPUT                                                                       */
/*      E_ID                Invalid ID number                                   */
/*      E_CTX               Context error                                       */
/*      E_QOVR              Queue overflow                                      */
/*      E_OBJ               Object state error                                  */
/*      E_NOEXS             Non-existent object                                 */
/*      E_OK                Normal completion                                   */
/*                                                                              */
/* CALLS                                                                        */
/*      _kernel_task_tcb            Get tcb pointer                             */
/*      _tx_thread_suspend          Suspend thread                              */
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
/*  2009/07/10      M. Miyashita    version 2.2, Modified comment(s),           */
/*                                  Current task information is acquired        */
/*                                  directly.                                   */
/*                                  Before using ThreadX API, it changed so     */
/*                                  that interruption might be enabled.         */
/*  2016/04/12      M. Miyashita    version 2.2n, Modified comment(s),          */
/*                  T. Shibuya      The task is a state waiting by ThreadX of   */
/*                                  the API to suspend state, fix the problem   */
/*                                  that is released also waiting state of      */
/*                                  ThreadX of the API when they resume.        */
/*                                                                              */
/********************************************************************************/
ER sus_tsk(ID tskid)
{
    ER rtn = E_OK;
    _KERNEL_UITRON_TSK* pTcb;
TX_INTERRUPT_SAVE_AREA

    CHECK_ID(TSK_SELF, _kernel_tsk_maxid, tskid)
    CHECK_TSK_CONTEXT()

    TX_DISABLE  /* Lockout interrupts. */
    pTcb = _kernel_task_tcb(tskid);
    if(pTcb!=NULL)
    {
        switch(pTcb->tskstat)
        {
        case TTS_RUN:
        case TTS_RDY:
            if(_tx_thread_current_ptr==&pTcb->thread && !DISPATCH_ENABLE)
            {
                rtn = E_CTX;    /* Context error. */
            }
            else
            {
				if(TX_SLEEP<=pTcb->thread.tx_thread_state)
				{
					/* Just set the delayed suspension flag.  */
					pTcb->thread.tx_thread_delayed_suspend = TX_TRUE;

					pTcb->tskstat = TTS_WAS;
					pTcb->suscnt = 1;   /* Set a suspend demand. */
					break;
				}

                pTcb->tskstat = TTS_SUS;
                pTcb->suscnt = 1;   /* Set a suspend demand. */

                if(_tx_thread_current_ptr==&pTcb->thread)
                {
                    pTcb->wait_rtn = E_OK;

                    /* Setup cleanup routine pointer.  */
                    pTcb->thread.tx_thread_suspend_cleanup = _kernel_task_cleanup;

                    /* Set the state to suspended.  */
                    pTcb->thread.tx_thread_state = TX_SUSPENDED;

                    /* Set the suspending flag.  */
                    pTcb->thread.tx_thread_suspending = TX_TRUE;

                    /* Setup the timeout period.  */
                    pTcb->thread.tx_thread_timer.tx_timer_internal_remaining_ticks = TX_WAIT_FOREVER;

                    _tx_thread_preempt_disable++;   /* Temporarily disable preemption.  */
                    TX_RESTORE  /* Restore interrupts. */

                    _tx_thread_system_suspend(&pTcb->thread);

                    TX_DISABLE  /* Lockout interrupts. */
                    pTcb->tskstat = TTS_RDY;
                    rtn = pTcb->wait_rtn;
                }
                else
                {
                    /* Setup cleanup routine pointer.  */
                    pTcb->thread.tx_thread_suspend_cleanup = _kernel_task_cleanup;

                    /* Set the state to suspended.  */
                    pTcb->thread.tx_thread_state = TX_SUSPENDED;

                    /* Set the suspending flag.  */
                    pTcb->thread.tx_thread_suspending = TX_TRUE;

                    /* Setup the timeout period.  */
                    pTcb->thread.tx_thread_timer.tx_timer_internal_remaining_ticks = TX_WAIT_FOREVER;

                    _tx_thread_preempt_disable++;   /* Disable preemption. */
                    TX_RESTORE  /* Restore interrupts. */

                    _tx_thread_system_suspend(&pTcb->thread);

                    TX_DISABLE  /* Lockout interrupts. */
                }
            }
            break;

        case TTS_WAI:
            pTcb->tskstat = TTS_WAS;
            pTcb->suscnt = 1;   /* Set a suspend demand. */

			if(TX_SLEEP<=pTcb->thread.tx_thread_state)
			{
				/* Just set the delayed suspension flag.  */
				pTcb->thread.tx_thread_delayed_suspend = TX_TRUE;
			}
            break;

        case TTS_SUS:
        case TTS_WAS:
            if(pTcb->suscnt<TMAX_SUSCNT)
            {
                pTcb->suscnt++; /* Increment of a suspend demand. */
            }
            else
            {
                rtn = E_QOVR;   /* Overflow of a demand number. */
            }
            break;

        case TTS_DMT:
        case TTS_NONE:
        default:
            rtn = E_OBJ;    /* Object error */
            break;
        }
    }
    else
    {
        rtn = E_NOEXS;  /* The object is not registered. */
    }
    TX_RESTORE  /* Restore interrupts. */

    return rtn;
}

