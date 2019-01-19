@ IsEqual checks to see if your number is a valid 12-bit immediate encodable
@ number. If so, '1' is the return value for r0. This used to be a linear
@ search through the lookup table, but that could get time consuming, even
@ though it's a simpler method. The below method starts in the middle of the
@ index and does the divide and conquer up/down by half thing. This is much
@ much faster

isequal:
	@ Check to see if number is a valid 12-bit imm encodable number
	@----------------------------------------------------------------------
	@ Init
	push 	{lr}
	ldr	r1, =immvals		@ Get initial offset of all valid values
	mov	r3, #0			@ Init return value (default no-match)
	mov	r4, #1536
	mov	r6, #1536
	mov	r7, #0			@ Last Run Flag

isequal_main:
	bl	isequal_nextvalue	@ Gets the next value to check

	cmp	r2, r0			@ Compare current number with supplied one
	moveq	r3, #1			@ It's a match
	beq	isequal_done

	@ Is this the last Index to check?
	cmp	r7, #2			@ Sometimes we need that extra run
	beq	isequal_done

	@ Get next offset
	bl	isequal_nextoffset

	b	isequal_main		@ Check next digit


isequal_done:
	mov	r0, r3			@ Return 1 for match, 0 for non-match
	pop 	{lr}
	bx	lr

isequal_nextvalue:
	push	{lr}
	mov	r5, r4		@ Get current offset index number
	lsl	r5, r5, #2	@ Multiply by 4 for word size adjustment
	add	r5, r1		@ Add offset from immvals start address
	ldr	r2, [r5]	@ Get the value
	pop	{lr}
	bx	lr

isequal_nextoffset:
	push	{lr}
	cmp	r6, #1		@ Last Div
	lsrne	r6, r6, #1	@ Divide tree modifier by 2
	addeq	r7, #1		@ Set Last Run Flag if last Div
        cmp     r0, r2          @ Compare user number with immval number
	addhi	r4, r6
	subls	r4, r6
	pop	{lr}
	bx	lr

.include "ValidImms.h"  @ Incudes 'immvals' array
