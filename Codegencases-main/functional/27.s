	.file	"27.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -112
	sd ra, 80(sp)
	sd s1, 88(sp)
	sd s2, 96(sp)
	sd s3, 104(sp)
	li s1, 1
	li s3, 5
	li s2, 2
.L0_0:
	sw s3, 0(sp)
	sw s3, 16(sp)
	sw s1, 32(sp)
	li ra, -2
	sw ra, 48(sp)
	sw s2, 64(sp)
	lw t0, 48(sp)
	mul t0, t0, s1
	div t0, t0, s2
	blt t0, zero, .L23_3
.L11_1:
	lw t1, 0(sp)
	lw t0, 16(sp)
	sub t0, t1, t0
	beq t0, zero, .L26_4
.L17_2:
	lw t0, 32(sp)
	addi t0, t0, 3
	rem t0, t0, s2
	beq t0, zero, .L26_4
.L23_3:
	lw t0, 64(sp)
	mv a0, t0
	call print_int
.L26_4:
	lw t0, 48(sp)
	rem t0, t0, s2
	addi t0, t0, 67
	blt t0, zero, .L44_7
.L32_5:
	lw t1, 0(sp)
	lw t0, 16(sp)
	sub t0, t1, t0
	beq t0, zero, .L47_8
.L38_6:
	lw t0, 32(sp)
	addi t0, t0, 2
	rem t0, t0, s2
	beq t0, zero, .L47_8
.L44_7:
	li ra, 4
	sw ra, 64(sp)
	lw t0, 64(sp)
	mv a0, t0
	call print_int
.L47_8:
	mv a0, zero
	ld ra, 80(sp)
	ld s1, 88(sp)
	ld s2, 96(sp)
	ld s3, 104(sp)
	addi sp, sp, 112
	ret
	.size	main, .-main

