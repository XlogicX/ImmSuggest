# ImmSuggest
Suggests a series of MOV and ADD instructions to use to get any 32-bit value into a register with Imm12 ARM encodings

# Assemble
as ImmSuggest.s -o ImmSuggest.o && ld ImmSuggest.o -o ImmSuggest

# Usage
You provide an integer as an argument (ideally something that fits into 32-bits), and it gives you the instruction(s) that will get that number into your register, some way or another. If your number doesn't fit in one instruction, the program will first display the closest surrounding numbers that would fit, as in: lower < your number > higher

# Usage Demo
![alt tag](https://github.com/XlogicX/ImmSuggest/blob/master/demo.png)
