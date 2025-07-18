	.file	"22.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.globl	arr_obj
	.data
	.align	3
	.type	arr_obj, @object
	.size	arr_obj, 24
arr_obj:
	.word 1, 2, 33, 4, 5, 6

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -64
	sd ra, 32(sp)
	sd s0, 40(sp)
	sd s2, 48(sp)
	li s0, 1
	li s2, 6
.L0_0:
	sw zero, 0(sp)
	sw zero, 16(sp)
	lw t0, 0(sp)
	bge t0, s2, .L23_4
.L6_1:
.L8_2:
	lw t2, 16(sp)
	la t1, arr_obj
	lw t0, 0(sp)
	li ra, 4
	mul t0, t0, ra
	add t0, t1, t0
	lw t0, 0(t0)
	add t0, t2, t0
	sw t0, 16(sp)
	lw t0, 0(sp)
	addi t0, t0, 1
	sw t0, 0(sp)
.L19_3:
	lw t0, 0(sp)
	blt t0, s2, .L8_2
.L23_4:
	lw t0, 16(sp)
	mv a0, t0
	ld ra, 32(sp)
	ld s0, 40(sp)
	ld s2, 48(sp)
	addi sp, sp, 64
	ret
	.size	main, .-main

