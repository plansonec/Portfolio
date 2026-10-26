@ CS 413
@ Fall 2026
@ Author: Emma Planson
@ Purpose: Simulates the operation of a coffee maker (Keurig). The machine
@          manages a 48 oz water reservoir, prompts user for cup sizes
@          (Small 6 oz, Medium 8 oz, Large 10 oz), brews coffee, tracks
@          dispensed cup counts, provides a hidden status display, and
@          automatically shuts down when water drops below 6 oz.

@ Commands to run:
@ Assemble: as -o lab3.o lab3.s
@ Link: gcc -z noexecstack -o lab3 lab3.o
@ Run: ./lab3; echo$?
@ Debug: gdb ./lab3

.text
.global main

@ Main Routine
main:
    push    {fp, lr}
    add     fp, sp, #4

main_loop:
    @ Display welcome and instruction message
    ldr     r0, =str_wel
    bl      printf

prompt_welcome:
    @ Read user input character
    ldr     r0, =fmt_char
    ldr     r1, =char_in
    bl      scanf
    cmp     r0, #1
    blt     end_prog

    @ Clear remaining characters up to newline
    bl      flush_input

    ldr     r1, =char_in
    ldrb    r1, [r1]

    @ Check if hidden code entered (H / h)
    cmp     r1, #'H'
    beq     show_hidden_welcome
    cmp     r1, #'h'
    beq     show_hidden_welcome

    @ Check if turn off selected (T / t)
    cmp     r1, #'T'
    beq     turn_off
    cmp     r1, #'t'
    beq     turn_off

    @ Check if begin brewing selected (B / b)
    cmp     r1, #'B'
    beq     prompt_cup_size
    cmp     r1, #'b'
    beq     prompt_cup_size

    @ Error handling for invalid input at welcome screen
    ldr     r0, =str_err
    bl      printf
    b       main_loop

show_hidden_welcome:
    @ Display inventory stats and re-prompt welcome menu
    bl      show_hidden
    b       main_loop

@ Cup Size Selection
prompt_cup_size:
    @ Display cup sizes to user
    ldr     r0, =str_size
    bl      printf

    @ Read cup size choice
    ldr     r0, =fmt_char
    ldr     r1, =char_in
    bl      scanf
    cmp     r0, #1
    blt     end_prog

    bl      flush_input

    ldr     r1, =char_in
    ldrb    r1, [r1]

    @ Allow hidden code entry at cup size prompt
    cmp     r1, #'H'
    beq     show_hidden_size
    cmp     r1, #'h'
    beq     show_hidden_size

    @ Allow turn off entry at cup size prompt
    cmp     r1, #'T'
    beq     turn_off
    cmp     r1, #'t'
    beq     turn_off

    @ Route to cup sizes: Small (S / s / 1)
    cmp     r1, #'S'
    beq     select_small
    cmp     r1, #'s'
    beq     select_small
    cmp     r1, #'1'
    beq     select_small

    @ Medium (M / m / 2)
    cmp     r1, #'M'
    beq     select_med
    cmp     r1, #'m'
    beq     select_med
    cmp     r1, #'2'
    beq     select_med

    @ Large (L / l / 3)
    cmp     r1, #'L'
    beq     select_large
    cmp     r1, #'l'
    beq     select_large
    cmp     r1, #'3'
    beq     select_large

    @ Error handling for invalid cup selection
    ldr     r0, =str_err
    bl      printf
    b       prompt_cup_size

show_hidden_size:
    @ Display inventory stats and re-prompt size selection
    bl      show_hidden
    b       prompt_cup_size

select_small:
    @ Setup parameters for Small: 6 oz, pointer to cnt_S
    mov     r6, #6
    ldr     r5, =cnt_S
    b       check_water

select_med:
    @ Setup parameters for Medium: 8 oz, pointer to cnt_M
    mov     r6, #8
    ldr     r5, =cnt_M
    b       check_water

select_large:
    @ Setup parameters for Large: 10 oz, pointer to cnt_L
    mov     r6, #10
    ldr     r5, =cnt_L
    b       check_water

@ Water Reservoir Availability Verification
check_water:
    @ Load current reservoir level
    ldr     r4, =water_res
    ldr     r7, [r4]

    @ Error checking: compare available water against selected cup size
    cmp     r7, r6
    bge     ready_to_brew

    @ Insufficient water: display error and prompt for smaller size
    ldr     r0, =str_no_wat
    bl      printf
    b       prompt_cup_size

@ Ready to Brew & Dispensing Logic
ready_to_brew:
    @ Display Ready to Brew instructions
    ldr     r0, =str_ready
    bl      printf

prompt_brew:
    @ Read brew trigger input
    ldr     r0, =fmt_char
    ldr     r1, =char_in
    bl      scanf
    cmp     r0, #1
    blt     end_prog

    bl      flush_input

    ldr     r1, =char_in
    ldrb    r1, [r1]

    @ Allow hidden code entry at brew prompt
    cmp     r1, #'H'
    beq     show_hidden_brew
    cmp     r1, #'h'
    beq     show_hidden_brew

    @ Allow turn off entry at brew prompt
    cmp     r1, #'T'
    beq     turn_off
    cmp     r1, #'t'
    beq     turn_off

    @ Start brewing when B / b is entered
    cmp     r1, #'B'
    beq     dispense_coffee
    cmp     r1, #'b'
    beq     dispense_coffee

    @ Error handling for invalid brew trigger input
    ldr     r0, =str_err
    bl      printf
    b       prompt_brew

show_hidden_brew:
    @ Display inventory stats and re-prompt brew menu
    bl      show_hidden
    b       ready_to_brew

dispense_coffee:
    @ Deduct dispensed ounces from reservoir
    ldr     r4, =water_res
    ldr     r7, [r4]
    sub     r7, r7, r6
    str     r7, [r4]

    @ Increment cup count for the brewed size
    ldr     r8, [r5]
    add     r8, r8, #1
    str     r8, [r5]

    @ Display coffee dispensed message
    ldr     r0, =str_disp
    bl      printf

    @ Check if reservoir drops below minimum 6 oz
    ldr     r4, =water_res
    ldr     r7, [r4]
    cmp     r7, #6
    blt     refill_shutdown

    @ Return to main welcome loop if 6 oz or more remains
    b       main_loop

@ Termination & Subroutine Handlers
refill_shutdown:
    @ Display refill reservoir message and turn off machine
    ldr     r0, =str_refill
    bl      printf
    b       end_prog

turn_off:
    @ Display turn off message and shutdown
    ldr     r0, =str_off
    bl      printf
    b       end_prog

@ Subroutine: show_hidden
@ Purpose: Displays current water level and total cups brewed per size
show_hidden:
    push    {r4, lr}

    ldr     r0, =str_stat
    ldr     r1, =water_res
    ldr     r1, [r1]
    ldr     r2, =cnt_S
    ldr     r2, [r2]
    ldr     r3, =cnt_M
    ldr     r3, [r3]

    ldr     r4, =cnt_L
    ldr     r4, [r4]
    sub     sp, sp, #8
    str     r4, [sp]
    bl      printf
    add     sp, sp, #8

    pop     {r4, lr}
    bx      lr

@ Subroutine: flush_input
@ Purpose: Consumes remaining characters from stdin line buffer until '\n'
flush_input:
    push    {r4, lr}

flush_loop:
    bl      getchar
    cmp     r0, #10             @ Check for newline character '\n'
    beq     flush_done
    cmp     r0, #-1             @ Check for EOF
    beq     flush_done
    b       flush_loop

flush_done:
    pop     {r4, lr}
    bx      lr

@ Program Exit
end_prog:
    mov     r0, #0
    pop     {fp, lr}
    bx      lr

.data
@ Water reservoir variable initialized to 48 oz
water_res:  .word 48

@ Cup count tracking variables initialized to 0
cnt_S:      .word 0
cnt_M:      .word 0
cnt_L:      .word 0

@ Buffer for user character input
char_in:    .space 4

@ Formats and Display Strings
fmt_char:   .asciz " %c"

str_wel:    .asciz "\nWelcome to the Coffee Maker\nInsert K-cup and press B to begin making coffee.\nPress T to turn off the machine.\nSelection: "
str_size:   .asciz "\nSelect cup size:\nS - Small (6 oz)\nM - Medium (8 oz)\nL - Large (10 oz)\nSelection: "
str_no_wat: .asciz "\nNot enough water for selected size. Please select a smaller cup size.\n"
str_ready:  .asciz "\nReady to Brew\nPlace cup in tray\nPress B (and enter) to start brewing.\nSelection: "
str_disp:   .asciz "\nCoffee has been dispensed\n"
str_refill: .asciz "\nWater level below 6 oz. Please refill the reservoir.\nShutting down machine.\n"
str_off:    .asciz "\nTurning off the coffee machine. Goodbye!\n"
str_stat:   .asciz "\nWater level: %d\nSmall: %d\nMedium: %d\nLarge: %d\n"
str_err:    .asciz "\nInvalid selection. Try again.\n"

