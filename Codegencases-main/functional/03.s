	.file	"03.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -80
	sd ra, 64(sp)
	sd s0, 72(sp)
	li s0, 1
.L0_0:
	li ra, 8
	sw ra, 16(sp)
	li ra, 12
	sw ra, 32(sp)
	lw t1, 16(sp)
	lw t0, 32(sp)
	add t0, t1, t0
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 64(sp)
	ld s0, 72(sp)
	addi sp, sp, 80
	ret
	.size	main, .-main

