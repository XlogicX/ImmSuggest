@ Range is used when a supplied number doesn't fit neetly into a 12-bit
@ immediate encodable value. The return will be a pointer to the closest
@ value larger than the provided one. As a side-effect, decrementing the
@ pointer by 4 will give the next higher value. This used to be a linear
@ search through the lookup table, but that could get time consuming, even
@ though it's a simpler method. The below method starts in the middle of the
@ index and does the divide and conquer up/down by half thing. This is much
@ much faster

range:
	@ Init
	push 	{lr}
	ldr	r1, =immvals		@ Get initial offset of all valid values
        mov     r3, #0                  @ Init return value (default out of range)
        mov     r4, #1536
        mov     r6, #1536
        mov     r7, #0                  @ Last Run Flag

range_main:
	bl	range_nextvalue		@ Load next offset

	@cmp	r2, #4278190080		@ Did we hit the last value?
	@addeq	r1, #4
	@moveq	r0, r1
	@beq	range_done		@ We are at the end of the list

	@cmp	r2, r0			@ Compare current number with supplied one
	@movhi	r0, r1			@ Get the pointer if we past the number
	@bhi	range_done		@ We're done

	cmp	r7, #1
	moveq	r8, r2
	cmp	r7, #2
	moveq	r9, r2
	beq	range_done

	bl	range_nextoffset
	b	range_main		@ Repeat

range_done:
	cmp	r0, r8		@ If the next hi value is lower, keep
	movls	r1, r5
	subls	r1, #4
	cmp	r0, r9		@ If this next hi value is still lower, keep instead
	movls	r1, r5
	movhi	r1, r5
	addhi	r1, #4

	mov	r0, r1
	pop 	{lr}
	bx	lr

range_nextvalue:
        push    {lr}
        mov     r5, r4          @ Get current offset index number
        lsl     r5, r5, #2      @ Multiply by 4 for word size adjustment
        add     r5, r1          @ Add offset from immvals start address
        ldr     r2, [r5]        @ Get the value
        pop     {lr}
        bx      lr

range_nextoffset:
        push    {lr}
        cmp     r6, #1          @ Last Div
        lsrne   r6, r6, #1      @ Divide tree modifier by 2
        addeq   r7, #1          @ Set Last Run Flag if last Div
        cmp     r0, r2          @ Compare user number with immval number
        addhi   r4, r6
        subls   r4, r6
        pop     {lr}
        bx      lr
