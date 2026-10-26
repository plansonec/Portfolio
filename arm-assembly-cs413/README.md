# 32-bit ARMv4 Assembly Systems Suite & Accessible Reference (CS 413)

**Course:** CS 413 — Introduction to Digital Computer Architecture (University of Alabama in Huntsville, Fall 2026)  
**Author:** Emma Planson (`@plansonec`)  
**Tech Stack:** 32-bit ARMv4 Assembly (`.s`), GNU Assembler (`as`), GCC Linker (`gcc`), GDB Debugger, AAPCS Stack Conventions, Accessible Technical Documentation

## Executive Overview

This directory contains 32-bit ARM Assembly systems programs and an accessible architectural reference guide developed for **CS 413 (Intro to Digital Computer Architecture)** at UAH. The coursework demonstrates low-level hardware stack management, register isolation across subroutines, software-implemented integer division, 64-bit arithmetic overflow traps, finite-state machine (FSM) control flow, and screen-reader accessible documentation.

## Directory Contents

| File / Directory | Component Name | Key Architectural Concepts Demonstrated |
| :--- | :--- | :--- |
| `lab2_stack_calculator/lab2.s` | **Lab 2: Stack-Based Four-Function Calculator** | Passes operands and return values exclusively via the hardware stack (`PUSH`/`POP`), enforces strict caller/callee register isolation (`r4`/`r5` vs. `r10`/`r11`), implements division via repeated subtraction (`div_func`), and traps 32-bit signed addition/multiplication overflows (`ADDS`/`BVC` and 64-bit `SMULL`). |
| `lab3_coffee_maker_fsm/lab3.s` | **Lab 3: Coffee Maker Finite State Machine (Keurig Simulator)** | Models an embedded appliance controller tracking a `48 oz` water reservoir (`.word 48`) and cup-size counters (`Small 6 oz`, `Medium 8 oz`, `Large 10 oz`), with character stream flushing (`flush_input`), hidden diagnostic telemetry (`H`/`h` -> `show_hidden`), and automatic low-water shutdown (`< 6 oz`). |
| `reference/ARM_Assembly_Reference_Card_Accessible.md` | **Accessible ARMv4 Reference Card** | A screen-reader accessible, semantic Markdown transcription of the 32-bit ARMv4 reference card, expanding every instruction mnemonic, condition code (`CPSR`), addressing mode, and barrel shifter operation with explicit table headers for NVDA, JAWS, and VoiceOver users. |
| `Makefile` | **Build Automation** | Assembles and links `lab2` and `lab3` with non-executable stack protection (`-z noexecstack`). |

## Deep Dive: Program Architectures

### 1. Stack-Based Four-Function Integer Calculator (`lab2_stack_calculator/lab2.s`)

Unlike standard C ABI calls that pass arguments in `r0`–`r3`, `lab2.s` implements a **pure stack-passing calling convention** with strict register isolation between `main` and all arithmetic subroutines:

- **Caller (`main`) Register Allocation:**
  - `r4`: First validated non-negative integer operand
  - `r5`: Second validated non-negative integer operand
  - `r6`: Menu operation selector (`1` = Add, `2` = Subtract, `3` = Multiply, `4` = Divide)
  - `r7`, `r8`: Preserved copies of original inputs for formatted `printf` output
- **Stack Parameter Protocol (`PUSH` / `POP`) & Register Isolation:**
  - Before calling `BL add_func`, `BL sub_func`, `BL mul_func`, or `BL div_func`, `main` executes `PUSH {r4, r5}`.
  - Inside each subroutine, operands are popped into **distinct upper registers** (`POP {r10, r11}`), computed, and pushed back onto the top of the stack (`PUSH {r12}`, `PUSH {r10}`, or `PUSH {r10, r11}`).
- **Hardware Overflow & Exception Handling:**
  - **Addition (`add_func`):** Uses `ADDS r12, r10, r11` to update CPSR flags and branches on `BVC` (Branch if Overflow Clear). If signed 32-bit overflow occurs (`> 2,147,483,647`, e.g., `2,147,449,525 + 1,947,583,648`), sets `r0 = 1` and prints an overflow diagnostic.
  - **Multiplication (`mul_func`):** Because 32-bit `MUL` silently truncates upper bits, `mul_func` uses 64-bit Signed Multiply Long (`SMULL r2, r12, r10, r11`) and verifies that the upper 32-bit register `r12 == 0` and the sign bit of `r2` (`CMP r2, #0`) did not wrap negative.
  - **Division (`div_func`):** Because ARMv4 lacks a hardware integer division instruction, `div_func` implements an iterative subtraction algorithm (`div_subtract_loop`), returning both the **quotient** (`r10`) and **remainder** (`r11`) on the hardware stack, while rejecting division by zero upfront.
  - **Input Stream Sanitization (`clear_input_buffer`):** Consumes malformed non-integer characters via `getchar` until newline (`#10`) or `EOF` (`#-1`) to prevent infinite `scanf` loops.

### 2. Embedded Coffee Maker Finite State Machine (`lab3_coffee_maker_fsm/lab3.s`)

Simulates the embedded control logic of a Keurig-style single-serve coffee maker managing a **48 oz water reservoir**:

- **State Transitions:**
  1. **Welcome / Idle State (`main_loop`):** Prompts user to insert a K-cup and press `B` (Begin brewing), `T` (Turn off), or secret diagnostic code `H` (Hidden inventory telemetry).
  2. **Cup Size Dispatch (`prompt_cup_size`):** Accepts `S`/`1` (Small — 6 oz, pointer `=cnt_S`), `M`/`2` (Medium — 8 oz, pointer `=cnt_M`), or `L`/`3` (Large — 10 oz, pointer `=cnt_L`), loading target ounces into `r6` and the counter address into `r5`.
  3. **Reservoir Verification (`check_water`):** Compares current `water_res` (`r7`) against requested ounces (`r6`). If `r7 < r6` (for example, 8 oz remaining when a 10 oz Large cup is requested), alerts the user to select a smaller cup size without shutting down.
  4. **Dispense & Auto-Shutdown (`dispense_coffee`):** Deducts `r6` from `water_res`, increments the size-specific memory counter (`[r5]`), and checks whether `water_res < 6`. Once available water drops below 6 oz (insufficient for even a Small cup), branches to `refill_shutdown` and halts cleanly.
- **5-Argument Stack-Aligned `printf` Call (`show_hidden`):**
  - Displays `Water level`, `Small`, `Medium`, and `Large` counts in a single `printf` call by passing the format string in `r0`, the first three integers in `r1`–`r3`, and pushing the 4th integer (`cnt_L`) onto the 8-byte aligned stack (`sub sp, sp, #8` / `str r4, [sp]`) per the ARM AAPCS ABI.

## How to Assemble, Link, and Run

On an ARMv7/ARM32 Linux environment (or Raspberry Pi / UAH CS 413 lab server):

```bash
# Build both lab2 and lab3 executables
make all

# Run Lab 2 (Four-Function Stack Calculator)
./lab2

# Run Lab 3 (Coffee Maker State Machine)
./lab3
```
