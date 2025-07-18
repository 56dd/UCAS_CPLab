	.file	"10.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -32
	sd ra, 16(sp)
.L0_0:
	li ra, 2
	sw ra, 0(sp)
	lw t0, 0(sp)
	li ra, 10
	sub t0, ra, t0
	mv a0, t0
	ld ra, 16(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

