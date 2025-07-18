	.file	"29.cact"
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
	.word -1

	.globl	b_obj
	.data
	.align	3
	.type	b_obj, @object
	.size	b_obj, 4
b_obj:
	.word 1

	.text
	.align	1
	.globl	inc_a
	.type	inc_a, @function
inc_a:
	addi sp, sp, -32
	sd ra, 16(sp)
	sd s0, 24(sp)
	li s0, 1
.L0_0:
	li ra, 0
	sw ra, 0(sp)
	lw t0, a_obj
	sw t0, 0(sp)
	lw t0, 0(sp)
	addi t0, t0, 1
	sw t0, 0(sp)
	lw t0, 0(sp)
	sw t0, a_obj, ra
	lw t0, a_obj
	mv a0, t0
	ld ra, 16(sp)
	ld s0, 24(sp)
	addi sp, sp, 32
	ret
	.size	inc_a, .-inc_a

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -32
	sd ra, 16(sp)
	sd s1, 24(sp)
	li s1, 1
.L0_1:
	li ra, 5
	sw ra, 0(sp)
	lw t0, 0(sp)
	blt t0, zero, .L55_14
.L5_2:
.L7_3:
	addi sp, sp, -16
	sd t0, 0(sp)
	call inc_a
	mv t0, a0
	addi sp, sp, 16
	beq t0, zero, .L24_7
.L11_4:
	addi sp, sp, -16
	sd t0, 0(sp)
	call inc_a
	mv t0, a0
	addi sp, sp, 16
	beq t0, zero, .L24_7
.L15_5:
	addi sp, sp, -16
	sd t0, 0(sp)
	call inc_a
	mv t0, a0
	addi sp, sp, 16
	beq t0, zero, .L24_7
.L19_6:
	lw t1, a_obj
	lw t0, b_obj
	add t0, t1, t0
	sw t0, a_obj, ra
.L24_7:
	addi sp, sp, -16
	sd t0, 0(sp)
	call inc_a
	mv t0, a0
	addi sp, sp, 16
	li ra, 14
	blt t0, ra, .L39_10
.L28_8:
	addi sp, sp, -16
	sd t0, 0(sp)
	call inc_a
	mv t0, a0
	addi sp, sp, 16
	beq t0, zero, .L44_11
.L32_9:
	addi sp, sp, -16
	sd t1, 0(sp)
	call inc_a
	mv t1, a0
	addi sp, sp, 16
	addi sp, sp, -16
	sd t0, 0(sp)
	sd t1, 8(sp)
	call inc_a
	mv t0, a0
	ld t1, 8(sp)
	addi sp, sp, 16
	sub t0, t1, t0
	addi t0, t0, 1
	beq t0, zero, .L44_11
.L39_10:
	lw t0, b_obj
	sw t0, a_obj, ra
	lw t0, b_obj
	li ra, 2
	mul t0, t0, ra
	sw t0, b_obj, ra
	j .L47_12
.L44_11:
	call inc_a
	mv t0, a0
.L47_12:
	lw t0, 0(sp)
	addi t0, t0, -1
	sw t0, 0(sp)
.L51_13:
	lw t0, 0(sp)
	bge t0, zero, .L7_3
.L55_14:
	lw t1, a_obj
	lw t0, b_obj
	add t0, t1, t0
	mv a0, t0
	ld ra, 16(sp)
	ld s1, 24(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

