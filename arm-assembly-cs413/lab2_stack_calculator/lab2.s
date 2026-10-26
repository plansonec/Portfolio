@ File: lab2.s
@ Author: Emma Planson
@ Email: ecp0018@uah.edu
@ Course: CS413-02 Fall 2026
@ Purpose: Four-function integer calculator (+, -, *, /) in ARM Assembly.
@          Implements stack parameter passing, register isolation,
@          repeated subtraction division, and arithmetic overflow detection.

@ Use these commands to assemble, link, and run:
@    as -o lab2.o lab2.s
@    gcc -o lab2 lab2.o
@    ./lab2 ;echo $?

.text
.global main
main:
    PUSH {r4-r8, lr}

calc_main_loop:
    @ Display welcome message and instructions
    LDR r0, =msg_welcome
    BL printf
    LDR r0, =msg_instruct
    BL printf

prompt_num1:
    @ Prompt for first integer and read input from user
    LDR r0, =msg_prompt_n1
    BL printf
    SUB sp, sp, #8
    LDR r0, =fmt_int_in
    MOV r1, sp
    BL scanf

    @ Check if scanf successfully read an integer
    CMP r0, #1
    BNE num1_not_int

    LDR r4, [sp]
    ADD sp, sp, #8

    @ Check that first integer is non-negative and reprompt if invalid
    CMP r4, #0
    BGE prompt_op
    LDR r0, =err_negative
    BL printf
    B prompt_num1

num1_not_int:
    @ Clean up stack, clear input buffer, display error, and reprompt
    ADD sp, sp, #8
    BL clear_input_buffer
    LDR r0, =err_not_int
    BL printf
    B prompt_num1

prompt_op:
    @ Display operation menu and read operator choice (1-4)
    LDR r0, =msg_menu
    BL printf
    LDR r0, =msg_prompt_op
    BL printf
    SUB sp, sp, #8
    LDR r0, =fmt_int_in
    MOV r1, sp
    BL scanf

    @ Check if scanf successfully read an integer
    CMP r0, #1
    BNE op_not_int

    LDR r6, [sp]
    ADD sp, sp, #8

    @ Check that menu choice is within range 1 to 4
    CMP r6, #1
    BLT invalid_op
    CMP r6, #4
    BGT invalid_op
    B prompt_num2

op_not_int:
    @ Clean up stack, clear input buffer, and reprompt for operation
    ADD sp, sp, #8
    BL clear_input_buffer
    B invalid_op

invalid_op:
    @ Display invalid operation error and reprompt for choice
    LDR r0, =err_invalid_op
    BL printf
    B prompt_op

prompt_num2:
    @ Prompt for second integer and read input from user
    LDR r0, =msg_prompt_n2
    BL printf
    SUB sp, sp, #8
    LDR r0, =fmt_int_in
    MOV r1, sp
    BL scanf

    @ Check if scanf successfully read an integer
    CMP r0, #1
    BNE num2_not_int

    LDR r5, [sp]
    ADD sp, sp, #8

    @ Validate non-negative input and check for division by zero
    CMP r5, #0
    BLT num2_is_neg
    CMP r6, #4
    BNE dispatch_op
    CMP r5, #0
    BNE dispatch_op
    LDR r0, =err_div_zero
    BL printf
    B prompt_num2

num2_not_int:
    @ Clean up stack, clear input buffer, display error, and reprompt
    ADD sp, sp, #8
    BL clear_input_buffer
    LDR r0, =err_not_int
    BL printf
    B prompt_num2

num2_is_neg:
    @ Display negative input error and reprompt for second integer
    LDR r0, =err_negative
    BL printf
    B prompt_num2

dispatch_op:
    @ Preserve original inputs in r7 and r8, then branch to chosen operation
    MOV r7, r4
    MOV r8, r5
    CMP r6, #1
    BEQ call_add
    CMP r6, #2
    BEQ call_sub
    CMP r6, #3
    BEQ call_mul
    B call_div

call_add:
    @ Push operands, call addition subroutine, pop sum, and handle overflow
    PUSH {r4, r5}
    BL add_func
    POP {r4}
    CMP r0, #1
    BEQ add_overflow
    LDR r0, =msg_res_add
    MOV r1, r7
    MOV r2, r8
    MOV r3, r4
    BL printf
    B ask_repeat

add_overflow:
    @ Display addition overflow error message
    LDR r0, =err_add_ovf
    MOV r1, r7
    MOV r2, r8
    BL printf
    B ask_repeat

call_sub:
    @ Push operands, call subtraction subroutine, pop difference, and print result
    PUSH {r4, r5}
    BL sub_func
    POP {r4}
    LDR r0, =msg_res_sub
    MOV r1, r7
    MOV r2, r8
    MOV r3, r4
    BL printf
    B ask_repeat

call_mul:
    @ Push operands, call multiplication subroutine, pop product, and handle overflow
    PUSH {r4, r5}
    BL mul_func
    POP {r4}
    CMP r0, #1
    BEQ mul_overflow
    LDR r0, =msg_res_mul
    MOV r1, r7
    MOV r2, r8
    MOV r3, r4
    BL printf
    B ask_repeat

mul_overflow:
    @ Display multiplication overflow error message
    LDR r0, =err_mul_ovf
    MOV r1, r7
    MOV r2, r8
    BL printf
    B ask_repeat

call_div:
    @ Push operands, call division subroutine, pop quotient and remainder, and print results
    PUSH {r4, r5}
    BL div_func
    POP {r4, r5}
    SUB sp, sp, #8
    STR r5, [sp]
    LDR r0, =msg_res_div
    MOV r1, r7
    MOV r2, r8
    MOV r3, r4
    BL printf
    ADD sp, sp, #8
    B ask_repeat

ask_repeat:
    @ Prompt user to continue or quit, then repeat loop or clean up and exit
    LDR r0, =msg_continue
    BL printf
    SUB sp, sp, #8
    LDR r0, =fmt_int_in
    MOV r1, sp
    BL scanf

    @ Check if scanf successfully read an integer
    CMP r0, #1
    BNE repeat_not_int

    LDR r4, [sp]
    ADD sp, sp, #8

    @ Check for valid responses: 1 to continue, 0 to quit
    CMP r4, #1
    BEQ calc_main_loop
    CMP r4, #0
    BEQ exit_program

    @ Reprompt if integer was neither 1 nor 0
    LDR r0, =err_invalid_repeat
    BL printf
    B ask_repeat

repeat_not_int:
    @ Clean up stack, clear input buffer, and reprompt for continue choice
    ADD sp, sp, #8
    BL clear_input_buffer
    LDR r0, =err_invalid_repeat
    BL printf
    B ask_repeat

exit_program:
    @ Display goodbye message, set exit code 0, and return control to OS
    LDR r0, =msg_goodbye
    BL printf
    MOV r0, #0
    POP {r4-r8, pc}

add_func:
    @ Pop operands into r10/r11, add values, set overflow flag in r0, and push sum
    POP {r10, r11}
    ADDS r12, r10, r11
    MOV r0, #0
    BVC add_no_ovf
    MOV r0, #1
add_no_ovf:
    PUSH {r12}
    BX lr

sub_func:
    @ Pop operands into r10/r11, subtract values, and push difference
    POP {r10, r11}
    SUB r10, r10, r11
    PUSH {r10}
    BX lr

mul_func:
    @ Pop operands into r10/r11, multiply values, set overflow flag in r0, and push product
    POP {r10, r11}
    SMULL r2, r12, r10, r11
    MOV r0, #0
    CMP r12, #0
    BNE mul_has_ovf
    CMP r2, #0
    BGE mul_done
mul_has_ovf:
    MOV r0, #1
mul_done:
    MOV r10, r2
    PUSH {r10}
    BX lr

div_func:
    @ Pop operands into r10/r11 and initialize quotient counter
    POP {r10, r11}
    MOV r12, #0

div_subtract_loop:
    @ Repeatedly subtract divisor from dividend and increment quotient counter
    CMP r10, r11
    BLT div_loop_end
    SUB r10, r10, r11
    ADD r12, r12, #1
    B div_subtract_loop

div_loop_end:
    @ Move quotient and remainder into return registers and push both onto stack
    MOV r11, r10
    MOV r10, r12
    PUSH {r10, r11}
    BX lr

clear_input_buffer:
    @ Read characters from stdin until newline or EOF to clear the input stream
    PUSH {r4, lr}
clear_loop:
    BL getchar
    CMP r0, #10
    BEQ clear_done
    CMP r0, #-1
    BEQ clear_done
    B clear_loop
clear_done:
    POP {r4, pc}

.data
msg_welcome:        .asciz "\n==================================================\n   ARM Assembly Four-Function Integer Calculator\n==================================================\n"
msg_instruct:       .asciz "Instructions: Enter zero or positive integers.\nDivision by zero is prohibited.\n\n"
msg_prompt_n1:      .asciz "Enter first positive integer: "
msg_menu:           .asciz "Select operation:\n  1. Addition (+)\n  2. Subtraction (-)\n  3. Multiplication (*)\n  4. Division (/)\n"
msg_prompt_op:      .asciz "Enter choice (1-4): "
msg_prompt_n2:      .asciz "Enter second positive integer: "
msg_continue:       .asciz "\nDo you want to continue with another calculation? (1 = Yes, 0 = No): "
msg_goodbye:        .asciz "Exiting calculator. Goodbye!\n"
msg_res_add:        .asciz "\nResult: %d + %d = %d\n"
msg_res_sub:        .asciz "\nResult: %d - %d = %d\n"
msg_res_mul:        .asciz "\nResult: %d * %d = %d\n"
msg_res_div:        .asciz "\nResult: %d / %d quotient = %d  remainder = %d\n"
err_negative:       .asciz "Error: Input must be a positive integer or zero. Please re-enter.\n"
err_not_int:        .asciz "Error: Input must be a valid integer. Please re-enter.\n"
err_invalid_op:     .asciz "Error: Invalid operation choice. Must be 1, 2, 3, or 4.\n"
err_invalid_repeat: .asciz "Error: Please enter 1 to continue or 0 to quit.\n"
err_div_zero:       .asciz "Error: Division by zero is not allowed. Please enter a non-zero divisor.\n"
err_add_ovf:        .asciz "\nOverflow Error: %d + %d exceeds 32-bit signed range!\n"
err_mul_ovf:        .asciz "\nOverflow Error: %d * %d exceeds 32-bit signed range!\n"
fmt_int_in:         .asciz "%d"
