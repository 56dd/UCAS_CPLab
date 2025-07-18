	.file	"21.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	whileIf
	.type	whileIf, @function
whileIf:
	addi sp, sp, -64
	sd ra, 32(sp)
	sd s0, 40(sp)
	sd s2, 48(sp)
	li s0, 1
	li s2, 100
.L0_0:
	sw zero, 0(sp)
	sw zero, 16(sp)
	lw t0, 0(sp)
	bge t0, s2, .L34_10
.L6_1:
.L8_2:
	lw t0, 0(sp)
	li ra, 5
	bne t0, ra, .L14_4
.L12_3:
	li ra, 25
	sw ra, 16(sp)
	j .L26_8
.L14_4:
	lw t0, 0(sp)
	li ra, 10
	bne t0, ra, .L20_6
.L18_5:
	li ra, 42
	sw ra, 16(sp)
	j .L24_7
.L20_6:
	lw t0, 0(sp)
	li ra, 2
	mul t0, t0, ra
	sw t0, 16(sp)
.L24_7:
.L26_8:
	lw t0, 0(sp)
	addi t0, t0, 1
	sw t0, 0(sp)
.L30_9:
	lw t0, 0(sp)
	blt t0, s2, .L8_2
.L34_10:
	lw t0, 16(sp)
	mv a0, t0
	ld ra, 32(sp)
	ld s0, 40(sp)
	ld s2, 48(sp)
	addi sp, sp, 64
	ret
	.size	whileIf, .-whileIf

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -16
	sd ra, 0(sp)
.L0_11:
	addi sp, sp, -16
	sd t0, 0(sp)
	call whileIf
	mv t0, a0
	addi sp, sp, 16
	mv a0, t0
	ld ra, 0(sp)
	addi sp, sp, 16
	ret
	.size	main, .-main

