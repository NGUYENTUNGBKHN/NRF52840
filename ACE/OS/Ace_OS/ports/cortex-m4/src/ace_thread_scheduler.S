
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
    /* Enable interrupts */
    CPSIE   i

    /* Enter the scheduler for the first time.  */

    MOV     r0, #0x10000000                         // Load PENDSVSET bit
    MOV     r1, #0xE000E000                         // Load NVIC base
    STR     r0, [r1, #0xD04]                        // Set PENDSVBIT in ICSR
    DSB                                             // Complete all memory accesses
    ISB                                             // Flush pipeline

__loop:                                             // wait pendSV event to happen
    b __loop
// }

// void SysTick_Handler()
// {
    .global SysTick_Handler
    .syntax unified
    .thumb_func
SysTick_Handler:
    MOV     r0, #0x10000000                         // Load PENDSVSET bit
    MOV     r1, #0xE000E000                         // Load NVIC base
    STR     r0, [r1, #0xD04]                        // Set PENDSVBIT in ICSR
    DSB                                             // Complete all memory accesses
    ISB                                             // Flush pipeline
    BX      LR
// }

// void PendSV_Handler()
// {
    .global PendSV_Handler
    .syntax unified
    .thumb_func
PendSV_Handler:
    @ CPSID   i                                 // Disable interrupt
    @ PUSH    {R0, LR}                          // Save LR
    @ BL      _ace_excution_thread_exit         // Call exit function
    @ POP     {R0, LR}
    @ CPSIE   i                                 // Enable interrupt
    LDR     R0, =_ace_thread_current_ptr        // Get address of _ace_thread_current_ptr
    LDR     R1, =_ace_thread_created_ptr        // Get address of _ace_thread_created_ptr
    LDR     R2, [R0]                            // Ge value of _ace_thread_current_ptr, that is *_ace_thread_current_ptr
    CBZ     R2, __ace_ts_new                    // If _ace_thread_current_ptr = NULL to jump __ace_ts_new

__ace_ts_save:                              
    /* Store old context */
    MRS     R0, PSP                         // Move PSP to R0
    STMDB   R0!, {R4-R11, LR}               // Store R4-R11 and LR to address R0
    

    /* thread current = next of thread current */
    LDR     R1, =_ace_thread_current_ptr    // Get address of _ace_thread_current_ptr
    LDR     R2, [R1]
    STR     R0, [R2, #8]

    LDR     R3, [R2, #28]
    STR     R3, [R1]

    LDR     R2, [R3, #24]
    CBZ     R2, __ace_ts_wait
    /* Recover PSP and preserve current thread context. */
__ace_ts_run:
    LDR     R2, [R3, #8]
    LDMIA   R2!, {R4-R11, LR}
    MSR     PSP, R2

    BX      LR
__ace_ts_new:
    LDR     R2, [R1]                        // Get value _ace_thread_created_ptr
    STR     R2, [R0]                        // Store it in _ace_thread_current_ptr
    MOV     R2, #0
    MSR     APSR_nzcvq, R2
    LDR     R3, [R0]
    b __ace_ts_run
__ace_ts_wait:
    b __ace_ts_wait
// }
