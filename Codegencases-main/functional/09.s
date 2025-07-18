	.file	"09.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	defn
	.type	defn, @function
defn:
	addi sp, sp, -16
	sd ra, 0(sp)
.L0_0:
	li a0, 4
	ld ra, 0(sp)
	addi sp, sp, 16
	ret
	.size	defn, .-defn

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -32
	sd ra, 16(sp)
.L0_1:
	li ra, 0
	sw ra, 0(sp)
	addi sp, sp, -16
	sd t0, 0(sp)
	call defn
	mv t0, a0
	addi sp, sp, 16
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 16(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

