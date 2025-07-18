	.file	"07.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.globl	a_obj
	.section .rodata
	.align	3
	.type	a_obj, @object
	.size	a_obj, 20
a_obj:
	.word 0, 1, 2, 3, 4

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -16
	sd ra, 0(sp)
.L0_0:
	la t0, a_obj
	addi t0, t0, 16
	lw t0, 0(t0)
	mv a0, t0
	ld ra, 0(sp)
	addi sp, sp, 16
	ret
	.size	main, .-main

