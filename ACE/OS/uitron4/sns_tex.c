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
/*  sns_tex.c                                                                   */
/*  uITRON Library for ThreadX.(GR-TXi4)                                        */
/*                                                                              */
/*  Sence task exception                                                        */
/*                                                                              */
/********************************************************************************/

#include "txi_knl.h"

/********************************************************************************/
/*                                                                              */
/* FUNCTION                                                                     */
/*      sns_tex                                                                 */
/*                                                                              */
/* AUTHOR                                                                       */
/*      M. Miyashita, Grape Systems Inc.                                        */
/*                                                                              */
/* DESCRIPTION                                                                  */
/*      Reference task exception handling state.                                */
/*                                                                              */
/* INPUT                                                                        */
/*      NONE                                                                    */
/*                                                                              */
/* OUTPUT                                                                       */
/*      TRUE                Task exception handling disable                     */
/*      FALSE               Task exception handling enable                      */
/*                                                                              */
/* CALLS                                                                        */
/*      _kernel_thread_to_task      Get tcb pointer from thread control block   */
/*                                                                              */
/* CALLED BY                                                                    */
/*      Application                                                             */
/*                                                                              */
/* ALLOWED FROM                                                                 */
/*      Task context                                                            */
/*      Non-task context                                                        */
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
/*                                                                              */
/********************************************************************************/
BOOL sns_tex(void)
{
    BOOL rtn = TRUE;
    _KERNEL_UITRON_TSK* pTcb;
TX_INTERRUPT_SAVE_AREA

    TX_DISABLE  /* Lockout interrupts. */
    pTcb = _kernel_thread_to_task(_tx_thread_current_ptr);
    if(pTcb!=NULL)
    {
        rtn = ((pTcb->texstat&TTEX_DIS)!=0);
    }
    TX_RESTORE  /* Restore interrupts. */

    return rtn;
}

