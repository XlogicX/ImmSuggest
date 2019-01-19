@ PrintD takes a register as an argument (expecting unsigned integer data) and
@ prints this number to STDOUT as a string. The argument comes in on r0.
.include "softdiv.h"	@ Requires division, and div isn't supported on my pi

printd:
	push	{lr}
	mov	r4, #0	@ Null
	push	{r4}	@ Push null terminator to stack

convert_start:
	@ Modulus grind the register for decimal digits and push them to stack
	@----------------------------------------------------------------------
	mov	r1, #10		@ The divisor
	bl	softdiv		@ Divide argument by 10
	add	r3, #0x30	@ Convert digit to ASCII
printd_ret:
	cmp	r3, #0x39	@ Weird Edge case :(
	movgt	r3, #0x30
	push	{r3}		@ Push adjusted digit to stack

	cmp	r0, #0		@ Is it null BTW? are we done?
	bne	convert_start	@ If not, keep going

	@ Print the string from stack
	@----------------------------------------------------------------------
printst:
	pop	{r0}		@ Get a digit
	cmp	r0, #0		@ Is it the end?
	beq	done		@ Then get out
	mov	r7, #4		@ Otherwise, get ready to Write the digit
	mov	r0, #1		@ STDOUT
	mov	r1, sp		@ next digit is on the stack
	sub	r1, #4		@ but 4 bytes prior
	mov	r2, #1		@ one character to print
	swi	#0
	b	printst		@ Do another

done:
	pop	{lr}
	bx	lr
