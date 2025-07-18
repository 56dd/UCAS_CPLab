	.file	"31.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.globl	k_obj
	.bss
	.align	3
	.type	k_obj, @object
	.size	k_obj, 4
k_obj:
	.word 0

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -96
	sd ra, 64(sp)
	sd s0, 72(sp)
	sd s1, 80(sp)
	sd s2, 88(sp)
	li s0, 1
	li s2, 11
	li s1, 10
.L0_0:
	li ra, 3389
	sd a0, -8(sp)
	sw ra, k_obj, a0
	ld a0, -8(sp)
	lw t0, k_obj
	li ra, 10000
	bge t0, ra, .L41_8
.L8_1:
	lw t0, 0(sp)
	addi t0, t0, 1
	sw t0, 0(sp)
	li ra, 112
	sw ra, 0(sp)
	lw t0, 0(sp)
	ble t0, s1, .L38_7
.L14_2:
.L16_3:
	lw t0, 0(sp)
	addi t0, t0, -88
	sw t0, 0(sp)
	lw t0, 0(sp)
	li ra, 1000
	bge t0, ra, .L32_5
.L22_4:
	li ra, 9
	sw ra, 16(sp)
	sw s2, 32(sp)
	sw s1, 48(sp)
	lw t1, 0(sp)
	lw t0, 48(sp)
	sub t0, t1, t0
	sw t0, 0(sp)
	sw s2, 48(sp)
	lw t1, 0(sp)
	lw t0, 48(sp)
	add t1, t1, t0
	lw t0, 32(sp)
	add t0, t1, t0
	sw t0, 0(sp)
.L32_5:
.L34_6:
	lw t0, 0(sp)
	bgt t0, s1, .L16_3
.L38_7:
	lw t0, 0(sp)
	mv a0, t0
	call print_int
.L41_8:
	lw t0, k_obj
	mv a0, t0
	ld ra, 64(sp)
	ld s0, 72(sp)
	ld s1, 80(sp)
	ld s2, 88(sp)
	addi sp, sp, 96
	ret
	.size	main, .-main

