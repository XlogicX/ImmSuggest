arg:
	push	{lr}

	@ Get pointer to the argument
	@----------------------------------------------------------------------
	mov	r0, sp		@ It's in the stack
	add	r0, #12		@ It's 12 bytes deep (this may not be portable)
	ldr	r0, [r0]	@ Get the value (its another pointer, to argument as string)
	cmp	r0, #0		@ Check to see if there isn't an arg (will be zero if no arg)
	beq	arg_no_arguments	@ Exit with error if so

	@ Process string into a number for register
	@----------------------------------------------------------------------
arg_process_string_init:
	mov	r1, #11		@ 'eleven' null
	push	{r1}		@ 0xb terminated string...
arg_process_string:
	ldrb	r1, [r0]	@ r1 should have next character
	cmp	r1, #0		@ if it's null
	beq	arg_math_init	@ we're done, start mathing
	sub	r1, #0x30	@ otherwise, covert from ascii to decimal
	push	{r1}		@ push it to stack
	add	r0, #1		@ get ready for next character
	b	arg_process_string	@ and process it

	@ Process the stack of digits and put the full number into our return register
	@----------------------------------------------------------------------
arg_math_init:
	mov	r3, #10		@ For multiplying by 10
	mov	r2, #1		@ Initial multiplier for one's place
	mov	r4, #0		@ Init total value to zero
arg_math:
	pop	{r1}		@ Get next char
	cmp	r1, #11		@ is it 'null'
	beq	arg_done	@ If so we are done
	mul	r1, r2		@ otherwise, multiply by current decimal place
	mul	r2, r3		@ crank up the decimal place for next digit
	add	r4, r1		@ Add it to total
	b	arg_math	@ repeat
arg_done:
	mov	r0, r4		@ Get our total into a proper return register of r0
	pop	{lr}
	bx	lr

	@ If no arguments were detected, let the user know and quit
	@----------------------------------------------------------------------
arg_no_arguments:
	mov	r7, #4		@ Write
	mov	r0, #1		@ STDOUT
	ldr	r1, =arg_noargs	@ Error message for no arguments
	mov	r2, #41		@ The message is 41 charaacters
	swi	#0		@ Print the message
	mov	r7, #1		@ Don't return to caller, just get out
	swi	#0

.data
	arg_noargs: .ascii "You must supply an argument (an integer)\n";
