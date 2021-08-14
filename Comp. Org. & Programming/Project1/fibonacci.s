/*
 * fibonacci.s
 *
 *  Created on: Oct 27, 2020
 *      Author: Matthew Vaysfeld
 */

 .text
 .global main
 .extern printf

main:
 .global fibonacci
ldr x0, =stack //load the stack pointer
mov sp, x0
sub sp, sp, #16
str x30, [sp]
bl fibonacci
.func fibonacci

fibonacci:

ldr x3, = num //address of &n
ldr x3, [x3] // derefrence
mov x1, #1 //fibCurrent
mov x2, #0 //fib previous
bl ffib // call recursive functiom
mov x1, x0
ldr x0, =string
stp x0,x1, [sp,#-16]!
bl printf
ldp x0, x1, [sp], #16

fibonacci_end:

ldr x30, [sp]
add sp, sp, #16
br x30 //return to caller

.endfunc

.func ffib


ffib:
stp x1,x2, [sp,#-16]! // save x1 and x2 on the stack
stp x3,x30, [sp,#-16]! // save x3 and x30 on the stack



ffibrec:
cmp x3, #1 // checks if x3 value is 1 (base case)
beq fib_end // if x3 is 1 then end the recursion (base case)
add x9, x1, x2 // adds fibCurrent to fibPrevious
mov x2, x1  // make fibPrevious = fibCurrent
mov x1, x9  // makes fibCurrent the sum of fibPrevious and fibCurrent
sub x3, x3, #1 //decrement n
bl ffibrec


fib_end:
mov x0, x1
ldp x3, x30, [sp], #16 //reload x3 and x30
ldp x1, x2, [sp], #16 //reload x1 and x2
br x30 //jump to caller
.endfunc

.data
string:
 .ascii "ans: %d \n\0"
num:
.dword 6
.bss
.align 8

out:
.space 8// space for result
.align 16
.space 4096 //space for stack
stack:
.space 32 //space for base address
.end
