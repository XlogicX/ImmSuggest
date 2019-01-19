@ ImmSuggest - Suggests a series of MOV and ADD instructions to use to get any 32-bit value into a register
@ Performance optimization opportunities in the range.h functionality

.include "printd.h"	@ Prints a register as ASCII decimal
.include "arg.h"	@ Gets argument from stdin as a non-ASCII register value

.text
.global _start

_start:
	@ Get the argument
	bl		arg		@ Get integer argument into r0
	ldr	r1, =argument	@ Get pointer for argument global var
	str	r0, [r1]	@ Store it

	@ See if it's an initial match
	bl	isequal		@ Is it equal to a value in our lookup table
	cmp	r0, #1		@ Check
	beq	oneop		@ If so, finish with the one 'mov' command

	@ Make note that this is our first run through our processing loop
	mov	r0, #0
	ldr	r1, =first_flag
	str	r0, [r1]	@ Init Flag for first run to 0

command_loop:
	@ While the number is NOT equal
	ldr	r0, =argument
	ldr	r0, [r0]
	bl	isequal
	cmp	r0, #1
	beq	final_command	@ Print the final ADD instruction if the value added is in the lookup table

	@ Based on Lookup table, get the closest valid numbers to the one we are working with
	ldr	r0, =argument	@ Get the current number
	ldr	r0, [r0]
	bl	range		@ At this point, r0 has pointer to upper

assignvars:
	@ Get upper and lower global vars populated
	ldr	r2, [r0]	@ Get value of upper number
	ldr	r1,=upper	@ Get address of 'upper'
	str	r2, [r1]	@ Store it
	sub	r0, #4		@ offset for the lower value
	ldr	r2, [r0]	@ Get value of lower number
	ldr	r1, =lower	@ Get address of 'lower'
	str	r2, [r1]	@ Store it
	add	r0, #4		@ Return pointer to upper value
	@ How much do we need to ADD from next lowest valid number to get to the number we're currently working with
	bl	cdiff
	ldr	r1, =argt
	str	r0, [r1]

	@ Issue a MOV if first run through, otherwise we will do an ADD
	ldr	r0, =first_flag
	ldr	r0, [r0]
	cmp	r0, #0
	beq	print_mov
	b	print

print_mov:
	@ Print Range
	ldr	r0, =lower
	ldr	r0, [r0]
	bl	printd		@ Prints Lower number

        mov     r7, #4
        mov     r0, #1
        ldr     r1, =lessthan
        mov     r2, #3
        swi     #0		@ Prints ' < '

        ldr     r0, =argument
        ldr     r0, [r0]
       	bl      printd		@ Prints Users number

        mov     r7, #4
        mov     r0, #1
        ldr     r1, =greaterthan
        mov     r2, #3
        swi     #0		@ Prints ' > '

        ldr     r0, =upper
        ldr     r0, [r0]
        bl      printd		@ Prints Upper Number

	mov	r7, #4
	mov	r0, #1
	ldr	r1, =newline
	mov	r2, #1
	swi	#0		@ Prints newline

	@ Print first part of string
	mov	r7, #4
	mov	r0, #1
	ldr	r1, =one_op
	mov	r2, #9
	swi	#0		@ Print 'MOV r0, #'

	@ Print 'lower'
	ldr	r0, =lower
	ldr	r0, [r0]
	bl	printd		@ Print The Lower number
	b	suggest_new

print:
       	@ Print first part of string
        mov     r7, #4
        mov     r0, #1
	ldr	r1, =add_op
        mov     r2, #9
        swi     #0		@ Print 'ADD r0, #'
        @ Print 'lower'
        ldr     r0, =lower
        ldr     r0, [r0]
        bl      printd		@ Print the Lower number

suggest_new:
	@ Print a newline
	mov	r7, #4
	mov	r0, #1
	ldr	r1, =newline
	mov	r2, #1
	swi	#0		@ Print the newline

	@ Get the current number and assign it as the 'argument'
	ldr	r0, =argt
	ldr	r0, [r0]
	ldr	r1, =argument
	str	r0, [r1]

	@ Specify that we are done with our first run in the command loop
	mov     r0, #1
        ldr     r1, =first_flag
        str     r0, [r1]
        b       command_loop

final_command:
        @ Print first part of string
        mov     r7, #4
        mov     r0, #1
	ldr	r1, =add_op
        mov     r2, #9
       	swi     #0		@ Print "ADD r0, #"

        ldr     r0, =argt
	ldr	r0, [r0]
	bl	printd		@ Print this last number

	@ Print newline
	mov	r7, #4
	mov	r0, #1
	ldr	r1, =newline
	mov	r2, #1
	swi	#0		@ Print the final newline and get out
	b	exit

oneop:
	@ For when the supplied argument already matches
	mov	r7, #4
	mov	r0, #1
	ldr	r1, =one_op
	mov	r2, #9
	swi	#0		@ Print "MOV r0, #"

	ldr	r0, =argument
	ldr	r0, [r0]
	bl	printd		@ Print the users number

        mov     r7, #4
        mov     r0, #1
        ldr     r1, =newline
        mov     r2, #1
        swi     #0		@ Print a newline and getout
	bl	exit

exit:
	mov	r7, #1
	swi	#0

.include "cdiff.h"		@ For finding the difference between Lowest match and User value
.include "range.h"		@ For finding the closest valid upper and lower value
.include "isequal.h"		@ For seeing if users value matches Valid ones

.data
	one_op: .ascii "mov r0, #"
	newline: .ascii "\n"
	add_op: .ascii "add r0, #"
	operation: .byte 0
	lessthan: .ascii " < "
	greaterthan: .ascii " > "

.bss
	.lcomm argument, 4
	.lcomm upper, 4
	.lcomm lower, 4
	.lcomm argt, 4
	.lcomm first_flag, 1
