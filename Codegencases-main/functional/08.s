	.file	"08.cact"
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

	.text
	.align	1
	.globl	func
	.type	func, @function
func:
	addi sp, sp, -32
	sd ra, 16(sp)
	sd s0, 24(sp)
	li s0, 1
.L1_0:
	sw a0, 0(sp)
	lw t0, 0(sp)
	addi t0, t0, -1
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 16(sp)
	ld s0, 24(sp)
	addi sp, sp, 32
	ret
	.size	func, .-func

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -32
	sd ra, 16(sp)
.L0_1:
	li ra, 10
	sd a0, -8(sp)
	sw ra, a_obj, a0
	ld a0, -8(sp)
	lw t0, a_obj
	addi sp, sp, -16
	sd t0, 0(sp)
	mv a0, t0
	call func
	mv t0, a0
	addi sp, sp, 16
	sw t0, 0(sp)
	lw t0, 0(sp)
	mv a0, t0
	ld ra, 16(sp)
	addi sp, sp, 32
	ret
	.size	main, .-main

