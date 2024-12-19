.thumb
.syntax unified


.type SVC_Handler, %function
.global SVC_Handler
SVC_Handler:
    /* Save user state */
    mrs r0, psp
    stmdb r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}
    /* Load kernel state */
    pop {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}
    msr psr, ip

    bx lr


.global activates
activates:
    /* Save kernel state */
    mrs ip, psr     @ chuyen gia tri thanh ghi trang thai vao ip 
                    @ ip 
    push {r4, r5, r6, r7, r8, r9, r10, r11, ip, lr}

    /* load user state */
    ldmia r0!, {r4, r5, r6, r7, r8, r9, r10, r11, lr}

    msr psp, r0
    /* check the situation and determine the transition */
    mov r0, #0xfffffff0
    cmp lr, r0
    /* if "lr" does not point to exception return, then switch to process stack */
    ittt ls
    movls r0, #3
    msrls control, r0
    isbls

    bx lr


    