.syntax unified
.cpu cortex-m4

.global power
.type power, %function
power:
    # Remember the ABI: we must not destroy the values in r4 to r11.
    # r12 is the scratch register that does not need to be preserved.
    # Arguments are placed in r0 and r1, the return value should go in r0.
    # To be certain, we just push all of them onto the stack.
    push {r4-r11}

    mov r2, r0
    mov r0, #1
    loop:
        cmp r1, #0
        beq done
        mul r0, r2
        sub r1, #1
        b loop
    done:

    # Finally, we restore the callee-saved register values and branch back.
    pop {r4-r11}
    bx lr
