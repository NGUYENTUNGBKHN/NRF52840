
#define SCB_ICSR            0xE000ED04
#define SCB_ICSR_PENDSVSET  0x10000000
    .global lastTask
    .global ace_thread
    .text
    .align 4
    .syntax unified
    @ SCB_ICSR            EQU     0xE000ED04    // Address register ICSR
    @ SCB_ICSR_PENDSVSET  EQU     0x10000000    // bit PENDSVSET (Bit 28)
// VOID   _ace_thread_start(VOID)
// {
    .global _ace_thread_start
    .thumb_func
_ace_thread_start:
    // lastTask = 0;
    MOV R0, #0
    LDR R2, =lastTask
    STR R0, [R2, #0]
    // Reset APSR
    MOV R0, #0
    MSR APSR_nzcvq, R0
    // Move the task's stack pointer address into R0
    LDR R0, =lastTask
    LDR R0, [R0]
    LDR R1, =ace_thread

    LDR R2, =28
    MUL R0, R0, R2
    ADD R1, R1, R0

    LDR R0, [R1, #8]

    MSR PSP, R0
    MOV R0, #3
    MSR CONTROL, R0
    ISB

    POP     {R4-R11, LR}
    LDR     R0, [SP]
    LDR     PC, [SP, #24] 
loop:
    b loop
// }

// void SysTick_Handler()
// {
    .global SysTick_Handler
    .syntax unified
    .thumb_func
SysTick_Handler:
    // load address SCB_ICSR to R0
    LDR R0, =SCB_ICSR
    // load value of SCB_ICSR to R1
    LDR R1, [R0]
    // R1 |= SCB_ICSR_PENDSVSET;
    ORR R1, R1, #SCB_ICSR_PENDSVSET
    // store value to R0
    STR     R1, [R0]
    // jmup return 
    BX      LR
// }

// void PendSV_Handler()
// {
    .global PendSV_Handler
    .syntax unified
    .thumb_func
PendSV_Handler:
    /* Save the old task's context */
    MRS     R0, PSP                        
    STMDB   R0!, {R4-R11, LR}               
     /* To get the task pointer address from result r0 */
    // This part stores the *saved* stack pointer (now in R0) into the current task's ACE_THREAD structure.
    // First, load the lastTask index.
    LDR     R1, =lastTask                   
    LDR     R2, [R1]                        

    // Calculate the address of ace_thread[lastTask]
    LDR     R3, =ace_thread                
    MOV     R4, #28            
    MUL     R2, R2, R4                      
    ADD     R3, R3, R2                      

    // Store the saved stack pointer (R0) into ace_thread[lastTask].ace_thread_stack_ptr
    STR     R0, [R3, #8] 

    // /* Find a new task to run */
scheduler_loop:
    // lastTask++;
    LDR     R0, =lastTask                   
    LDR     R1, [R0]                        
    ADD     R1, R1, #1                      

    // if (lastTask == MAX_STACKS)
    LDR     R2, =MAX_TASKS                 
    CMP     R1, R2                         
    BNE     skip_reset_lastTask          

    // lastTask = 0;
    MOV     R1, #0                       

skip_reset_lastTask:
    STR     R1, [R0]                      

    // if (ace_thread[lastTask].ace_in_use)
    // lastTask is in R1
    MOV     R0, R1                       

    LDR     R1, =ace_thread              
    
    // Calculate the address of ace_thread[lastTask]
    LDR     R2, =28          
    MUL     R0, R0, R2                      
    ADD     R1, R1, R0                     

    // Load ace_in_use (offset 24 bytes from struct start)
    LDRB    R0, [R1, #24]
    CMP     R0, #0                         
    BEQ     scheduler_loop              

    /* Move the task's stack pointer address into r0 */
    LDR     R0, [R1, #8] 

    /* Restore the new task's context and jump to the task */
    LDMIA   R0!, {R4-R11, LR}               

    MSR     PSP, R0
    BX      LR
// }
