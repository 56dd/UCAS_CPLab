	.file	"18.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	ifElseIf
	.type	ifElseIf, @function
ifElseIf:
	addi sp, sp, -64
	sd ra, 32(sp)
	sd s1, 40(sp)
	sd s0, 48(sp)
	li s0, 1
	li s1, 10
.L0_0:
	li ra, 5
	sw ra, 0(sp)
	sw s1, 16(sp)
	lw t0, 0(sp)
	li ra, 6
	beq t0, ra, .L10_2
.L6_1:
	lw t0, 16(sp)
	li ra, 11
	bne t0, ra, .L13_3
.L10_2:
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 32(sp)
	ld s1, 40(sp)
	ld s0, 48(sp)
	addi sp, sp, 64
	ret
.L13_3:
	lw t0, 16(sp)
	bne t0, s1, .L23_6
.L17_4:
	lw t0, 0(sp)
	bne t0, s0, .L23_6
.L21_5:
	li ra, 25
	sw ra, 0(sp)
	j .L41_11
.L23_6:
	lw t0, 16(sp)
	bne t0, s1, .L35_9
.L27_7:
	lw t0, 0(sp)
	li ra, -5
	bne t0, ra, .L35_9
.L31_8:
	lw t0, 0(sp)
	addi t0, t0, 15
	sw t0, 0(sp)
	j .L39_10
.L35_9:
	lw t0, 0(sp)
	li ra, 0
	sub t0, ra, t0
	sw t0, 0(sp)
.L39_10:
.L41_11:
.L43_12:
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 32(sp)
	ld s1, 40(sp)
	ld s0, 48(sp)
	addi sp, sp, 64
	ret
	.size	ifElseIf, .-ifElseIf

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -16
	sd ra, 0(sp)
.L0_13:
	addi sp, sp, -16
	sd t0, 0(sp)
	call ifElseIf
	mv t0, a0
	addi sp, sp, 16
	mv a0, t0
	call print_int
	li a0, 0
	ld ra, 0(sp)
	addi sp, sp, 16
	ret
	.size	main, .-main

