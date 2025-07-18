	.file	"23.cact"
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
	.word 1

	.globl	b_obj
	.data
	.align	3
	.type	b_obj, @object
	.size	b_obj, 4
b_obj:
	.word 0

	.globl	c_obj
	.data
	.align	3
	.type	c_obj, @object
	.size	c_obj, 4
c_obj:
	.word 1

	.globl	d_obj
	.data
	.align	3
	.type	d_obj, @object
	.size	d_obj, 4
d_obj:
	.word 2

	.globl	e_obj
	.data
	.align	3
	.type	e_obj, @object
	.size	e_obj, 4
e_obj:
	.word 4

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -32
	sd ra, 16(sp)
	sd s0, 24(sp)
	li s0, 1
.L0_0:
	li ra, 0
	sw ra, 0(sp)
	lw t1, a_obj
	lw t0, b_obj
	mul t1, t1, t0
	lw t0, c_obj
	div t2, t1, t0
	lw t1, e_obj
	lw t0, d_obj
	add t0, t1, t0
	beq t2, t0, .L25_2
.L12_1:
	lw t2, a_obj
	lw t1, b_obj
	lw t0, c_obj
	mul t0, t1, t0
	sub t3, t2, t0
	lw t2, d_obj
	lw t1, a_obj
	lw t0, c_obj
	div t0, t1, t0
	sub t0, t2, t0
	beq t3, t0, .L38_3
	j .L40_4
.L25_2:
	lw t2, a_obj
	lw t1, a_obj
	lw t0, b_obj
	add t0, t1, t0
	mul t1, t2, t0
	lw t0, c_obj
	add t2, t1, t0
	lw t1, d_obj
	lw t0, e_obj
	add t0, t1, t0
	bgt t2, t0, .L12_1
.L38_3:
	sw s0, 0(sp)
.L40_4:
	lw t0, 0(sp)
	mv a0, t0
	call print_int
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 16(sp)
	ld s0, 24(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

