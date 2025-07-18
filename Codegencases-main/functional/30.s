	.file	"30.cact"
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
	.word 7

	.text
	.align	1
	.globl	func
	.type	func, @function
func:
	addi sp, sp, -48
	sd ra, 32(sp)
	sd s0, 40(sp)
	li s0, 1
.L0_0:
	li ra, -1
	sw ra, 0(sp)
	lw t0, 16(sp)
	sw t0, 0(sp)
	sw s0, 16(sp)
	lw t1, 16(sp)
	lw t0, 0(sp)
	bne t1, t0, .L12_2
.L8_1:
	lw t0, 16(sp)
	addi t0, t0, 1
	sw t0, 16(sp)
	mv a0, s0
	ld ra, 32(sp)
	ld s0, 40(sp)
	addi sp, sp, 48
	ret
.L12_2:
	li a0, 0
	ld ra, 32(sp)
	ld s0, 40(sp)
	addi sp, sp, 48
	ret
	.size	func, .-func

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
	li s2, 100
.L0_3:
	sw zero, 0(sp)
	sw zero, 16(sp)
	lw t0, 16(sp)
	bge t0, s2, .L24_9
.L6_4:
.L8_5:
	addi sp, sp, -16
	sd t0, 0(sp)
	call func
	mv t0, a0
	addi sp, sp, 16
	bne t0, s0, .L16_7
.L12_6:
	lw t0, 0(sp)
	addi t0, t0, 1
	sw t0, 0(sp)
.L16_7:
	lw t0, 16(sp)
	addi t0, t0, 1
	sw t0, 16(sp)
.L20_8:
	lw t0, 16(sp)
	blt t0, s2, .L8_5
.L24_9:
	lw t0, 0(sp)
	bge t0, s2, .L30_11
.L28_10:
	mv a0, s0
	call print_int
	j .L32_12
.L30_11:
	mv a0, zero
	call print_int
.L32_12:
	mv a0, zero
	ld ra, 32(sp)
	ld s0, 40(sp)
	ld s2, 48(sp)
	addi sp, sp, 64
	ret
	.size	main, .-main

