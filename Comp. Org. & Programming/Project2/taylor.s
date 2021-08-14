/*
 * taylor.s
 *
 *  Created on: Dec 4, 2020
 *      Author: Matthew Vaysfeld
 */

.text
 .global main
 .extern printf

 main:
 .global taylor
sub sp, sp, #16
str x30, [sp]

taylor:
ldr x1, =i //address of &i
ldr x1, [x1] // derefrence
ldr x2, =x //address of &i
ldr d2, [x2] // derefrence
mov x3, #1
SCVTF d3, x3
b sum

print:
ldr x0, =string
str d0, [sp,#8]
bl printf
ldr d0, [sp,#8]
ldr x30, [sp]
add sp, sp, #16
br x30 //return to caller


sum:

sumfunc:
cmp x1, #0 // compares i to 0
beq sumend  // if i is 0 then go back to caller
sub x1, x1, #1 //decrement global i
fadd d0, d0, d3 // adds ith term to total
str d0, [sp,#8]
b ith //get ith term
b sumfunc


sumend:
b print


ith:
b factorial // do factorial of i (store fact(i) into x5)
i1:
b power //get power of x to i (store power(x,i) into d11)
i2:
mov x15, #1
SCVTF d15, x15
SCVTF d5, x5
fdiv d10, d15, d5 // 1/fact(i)
fmul d3, d10, d4 // 1/fact(i) * x^i
b sumfunc //go back to sum function



power:
mov x12, x1 // temp variable that equals i
mov x11, #1
SCVTF d4, x11

powerfunc:
cmp x12, #0
beq powend
fmul d4, d4, d2
sub x12, x12, #1
b powerfunc


powend:
b i2

factorial:
mov x5, #1
cmp x1, #0
beq factend
mov x13, x1

factfunc:
udiv x14, x1, x13
cmp x14, x1
beq factend
mul x5, x5, x13
sub x13, x13, #1
b factfunc



factend:
b i1


.data
string:
 .asciz "The approximation is %f\n"
 .balign 4
x:
.double 44
i:
.dword 12
.bss
.align 8
.end
