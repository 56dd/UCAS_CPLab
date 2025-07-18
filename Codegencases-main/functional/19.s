	.file	"19.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

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
.L0_0:
	sw zero, 0(sp)
	sw zero, 16(sp)
	lw t0, 0(sp)
	bge t0, s2, .L25_6
.L6_1:
.L8_2:
	lw t0, 0(sp)
	li ra, 50
	bne t0, ra, .L14_4
.L12_3:
	j .L25_6
.L14_4:
	lw t1, 16(sp)
	lw t0, 0(sp)
	add t0, t1, t0
	sw t0, 16(sp)
	lw t0, 0(sp)
	addi t0, t0, 1
	sw t0, 0(sp)
.L21_5:
	lw t0, 0(sp)
	blt t0, s2, .L8_2
.L25_6:
	lw t0, 16(sp)
	li ra, 256
	rem t0, t0, ra
	mv a0, t0
	ld ra, 32(sp)
	ld s0, 40(sp)
	ld s2, 48(sp)
	addi sp, sp, 64
	ret
	.size	main, .-main

