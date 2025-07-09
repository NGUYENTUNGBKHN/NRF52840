
#define SCB_ICSR            0xE000ED04
#define SCB_ICSR_PENDSVSET  0x10000000
    .global _ace_excution_thread_exit
    .global _ace_thread_current_ptr
    .global _ace_thread_created_ptr
    .text
    .align 4
    .syntax unified
    @ SCB_ICSR            EQU     0xE000ED04    // Address register ICSR
    @ SCB_ICSR_PENDSVSET  EQU     0x10000000    // bit PENDSVSET (Bit 28)
// VOID   _ace_thread_schedule(VOID)
// {
    .global _ace_thread_schedule
    .thumb_func
_ace_thread_schedule:
    LDR R0, =_ace_thread_current_ptr
    LDR R1, =_ace_thread_created_ptr     
    CBZ R1, __loop                      // If _ace_thread_created_ptr = NULL

    LDR R2, [R1]                        // Get value _ace_thread_created_ptr
    STR R2, [R0]                        // Store it in _ace_thread_current_ptr

    MOV R2, #0
    MSR APSR_nzcvq, R2

    LDR R2, [R0]
    LDR R1, [R2, #8]
    MSR PSP, R1
    MOV R2, #3
    MSR CONTROL, R2
    ISB 

    POP {R4 - R11, LR}
    LDR R0, [SP]

    LDR PC, [SP, #24]

__loop:                                   // wait pendSV event to happen
    b __loop
// }

// void SysTick_Handler()
// {
    .global SysTick_Handler
    .syntax unified
    .thumb_func
SysTick_Handler:
    LDR R0, =SCB_ICSR                   // load address SCB_ICSR to R0
    LDR R1, [R0]                        // load value of SCB_ICSR to R1
    ORR R1, R1, #SCB_ICSR_PENDSVSET     // R1 |= SCB_ICSR_PENDSVSET;
    STR     R1, [R0]                    // store value to R0
    BX      LR                          // jmup return 
// }

// void PendSV_Handler()
// {
    .global PendSV_Handler
    .syntax unified
    .thumb_func
PendSV_Handler:
    @ CPSID   i                           // Disable interrupt
    @ PUSH    {R0, LR}                    // Save LR
    @ BL      _ace_excution_thread_exit   // Call exit function
    @ POP     {R0, LR}
    @ CPSIE   i                           // Enable interrupt

    /* Store old context */
    MRS     R0, PSP
    STMDB   R0!, {R4-R11, LR}
    

    /* thread current = next of thread current */
    LDR     R1, =_ace_thread_current_ptr
    LDR     R2, [R1]
    STR     R0, [R2, #8]

    LDR     R3, [R2, #28]
    STR     R3, [R1]

    LDR     R2, [R3, #24]
    CBZ     R2, __ace_ts_wait
    /* Recover PSP and preserve current thread context. */
    LDR     R2, [R3, #8]
    LDMIA   R2!, {R4-R11, LR}
    MSR     PSP, R2

    BX      LR

__ace_ts_wait:
    b __ace_ts_wait
// }
