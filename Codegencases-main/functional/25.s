	.file	"25.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.globl	a_obj
	.bss
	.align	3
	.type	a_obj, @object
	.size	a_obj, 4
a_obj:
	.word 0

	.globl	b_obj
	.bss
	.align	3
	.type	b_obj, @object
	.size	b_obj, 4
b_obj:
	.word 0

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
	addi sp, sp, -16
	sd t0, 0(sp)
	call get_int
	mv t0, a0
	addi sp, sp, 16
	sw t0, a_obj, ra
	addi sp, sp, -16
	sd t0, 0(sp)
	call get_int
	mv t0, a0
	addi sp, sp, 16
	sw t0, b_obj, ra
	lw t1, a_obj
	lw t0, b_obj
	bne t1, t0, .L14_3
.L8_1:
	lw t0, a_obj
	li ra, 3
	beq t0, ra, .L14_3
.L12_2:
	sw s0, 0(sp)
	j .L16_4
.L14_3:
	li ra, 0
	sw ra, 0(sp)
.L16_4:
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 16(sp)
	ld s0, 24(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

