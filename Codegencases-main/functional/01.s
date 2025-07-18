	.file	"01.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.globl	a_obj
	.data
	.align	3
	.type	a_obj, @object
	.size	a_obj, 4
a_obj:
	.word 2

	.globl	b_obj
	.data
	.align	3
	.type	b_obj, @object
	.size	b_obj, 4
b_obj:
	.word 3

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -32
	sd ra, 16(sp)
.L0_0:
	li ra, 4
	sw ra, 0(sp)
	lw t1, 0(sp)
	lw t0, b_obj
	add t0, t1, t0
	mv a0, t0
	ld ra, 16(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

