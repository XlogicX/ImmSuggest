@ I didn't write this soft division routine, I just modified it. I wrote a
@ C program with a divide instruction in it, then used objdump -D to see
@ what libC did to acheive it (with it's divsi3 routine). I'm dumb at law
@ stuff, If I'm not attributing libc in the right way, even though it's
@ source code that I'm using, then I will correct the attribution if
@ someone complains. I simplified subroutine names and killed the divide
@ by 0 error handling, if that's a bad thing, cash me outside, how bou dah
@ I also commented out a lot of rsb instructions becuase I fucked up and
@ reversed a signed div function, so I just brazenly converted this to
@ unsigned-ish

softdiv:
	eor	ip, r0, r1
@	rsbmi	r1, r1, #0
	subs	r2, r1, #1
	beq	sub1
	movs	r3, r0
@	rsbmi	r3, r0, #0
	cmp	r3, r1
	bls	sub2
	tst	r1, r2
	beq	sub3
	clz	r2, r3
	clz	r0, r1
	sub	r2, r0, r2
	rsbs	r2, r2, #31
	addne	r2, r2, r2, lsl #1
	mov	r0, #0
	addne	pc, pc, r2, lsl #2
	nop
	cmp	r3, r1, lsl #31
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #31
	cmp	r3, r1, lsl #30
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #30
	cmp	r3, r1, lsl #29
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #29
	cmp	r3, r1, lsl #28
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #28
	cmp	r3, r1, lsl #27
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #27
	cmp	r3, r1, lsl #26
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #26
	cmp	r3, r1, lsl #25
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #25
	cmp	r3, r1, lsl #24
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #24
	cmp	r3, r1, lsl #23
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #23
	cmp	r3, r1, lsl #22
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #22
	cmp	r3, r1, lsl #21
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #21
	cmp	r3, r1, lsl #20
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #20
	cmp	r3, r1, lsl #19
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #19
	cmp	r3, r1, lsl #18
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #18
	cmp	r3, r1, lsl #17
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #17
	cmp	r3, r1, lsl #16
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #16
	cmp	r3, r1, lsl #15
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #15
	cmp	r3, r1, lsl #14
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #14
	cmp	r3, r1, lsl #13
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #13
	cmp	r3, r1, lsl #12
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #12
	cmp	r3, r1, lsl #11
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #11
	cmp	r3, r1, lsl #10
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #10
	cmp	r3, r1, lsl #9
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #9
	cmp	r3, r1, lsl #8
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #8
	cmp	r3, r1, lsl #7
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #7
	cmp	r3, r1, lsl #6
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #6
	cmp	r3, r1, lsl #5
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #5
	cmp	r3, r1, lsl #4
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #4
	cmp	r3, r1, lsl #3
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #3
	cmp	r3, r1, lsl #2
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #2
	cmp	r3, r1, lsl #1
	adc	r0, r0, r0
	subcs	r3, r3, r1, lsl #1
	cmp	r3, r1
	adc	r0, r0, r0
	subcs	r3, r3, r1
	cmp	ip, #0
@	rsbmi	r0, r0, #0
	bx	lr
sub1:
	teq	ip, r0
	rsbmi	r0, r0, #0
	bx	lr
sub2:
	movcc	r0, #0
	asreq	r0, ip, #31
	orreq	r0, r0, #1
	bx	lr
sub3:
	clz	r2, r1
	rsb	r2, r2, #31
	cmp	ip, #0
	lsr	r0, r3, r2
	rsbmi	r0, r0, #0
	bx	lr
