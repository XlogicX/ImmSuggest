@ Closest Difference:
@ signed_int = cdiff( * upper number)
@ Give this function a pointer to the number higher than the argument supplied,
@ this function will return which number (higher or lower) the argument is closest
@ to by giving the diff
@ I.E., the number supplied is 1001, and it is between 1000 and 1004. Give cdiff a
@ pointer to where 1004 is, and it will return '1', as it is 1 away from 1000. If
@ you gave it 1003 as an argument, it would return '-1'

cdiff:
	push	{lr}
	@ init vals
	mov	r3, #0
	mov	r4, #0

	@ r0 should be pointer to the upper number in range
	@ Get rest of arguments
	mov	r1, r0		@ Copy pointer
	sub	r1, #4		@ Adjust
	ldr	r0, [r0]	@ Upper number
	ldr	r1, [r1]	@ Lower number
	ldr	r2, =argument
	ldr	r2, [r2]	@ r2 has the number

	@ Get differences				1000 - 1001 - 1004
	sub	r4, r2, r1	@ value to add		1

	mov	r0, r4
	pop 	{lr}
	bx	lr
