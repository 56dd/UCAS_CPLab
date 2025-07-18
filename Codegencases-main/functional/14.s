	.file	"14.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -48
	sd ra, 32(sp)
	sd s0, 40(sp)
	li s0, 1
.L0_0:
	li ra, 10
	sw ra, 0(sp)
	li ra, 5
	sw ra, 16(sp)
	lw t1, 0(sp)
	lw t0, 16(sp)
	div t0, t1, t0
	mv a0, t0
	ld ra, 32(sp)
	ld s0, 40(sp)
	addi sp, sp, 48
	ret
	.size	main, .-main

