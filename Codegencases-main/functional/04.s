	.file	"04.cact"
	.option nopic
	.attribute arch, "rv64i2p0_m2p0_a2p0_f2p0_d2p0_c2p0"
	.attribute unaligned_access, 0
	.attribute stack_align, 16

	.globl	__a4_global_main_obj
	.data
	.align	3
	.type	__a4_global_main_obj, @object
	.size	__a4_global_main_obj, 32
__a4_global_main_obj:
	.word 0, 0, 0, 0, 0, 0, 0, 0

	.globl	__c4_global_main_obj
	.data
	.align	3
	.type	__c4_global_main_obj, @object
	.size	__c4_global_main_obj, 32
__c4_global_main_obj:
	.word 1, 2, 3, 4, 5, 6, 7, 8

	.globl	__e4_global_main_obj
	.data
	.align	3
	.type	__e4_global_main_obj, @object
	.size	__e4_global_main_obj, 32
__e4_global_main_obj:
	.word 1, 2, 3, 4, 5, 6, 7, 8

	.text
	.align	1
	.globl	main
	.type	main, @function
main:
	addi sp, sp, -128
	sd ra, 96(sp)
	sd s0, 104(sp)
	sd s1, 112(sp)
	li s0, 4
	li s1, 16
.L0_0:
	la ra, __a4_global_main_obj
	sd a0, -8(sp)
	ld a0, 0(ra)
	sd a0, 0(sp)
	ld a0, 8(ra)
	sd a0, 8(sp)
	ld a0, 16(ra)
	sd a0, 16(sp)
	ld a0, 24(ra)
	sd a0, 24(sp)
	ld a0, -8(sp)
	la ra, __c4_global_main_obj
	sd a0, -8(sp)
	ld a0, 0(ra)
	sd a0, 32(sp)
	ld a0, 8(ra)
	sd a0, 40(sp)
	ld a0, 16(ra)
	sd a0, 48(sp)
	ld a0, 24(ra)
	sd a0, 56(sp)
	ld a0, -8(sp)
	la ra, __e4_global_main_obj
	sd a0, -8(sp)
	ld a0, 0(ra)
	sd a0, 64(sp)
	ld a0, 8(ra)
	sd a0, 72(sp)
	ld a0, 16(ra)
	sd a0, 80(sp)
	ld a0, 24(ra)
	sd a0, 88(sp)
	ld a0, -8(sp)
	addi t0, sp, 32
	addi t0, t0, 16
	addi t0, t0, 4
	lw t1, 0(t0)
	addi t0, sp, 64
	sw t1, 0(t0)
	addi t0, sp, 32
	addi t0, t0, 8
	addi t0, t0, 4
	lw t1, 0(t0)
	addi t0, sp, 64
	addi t0, t0, 4
	sw t1, 0(t0)
	addi t0, sp, 64
	addi t0, t0, 24
	addi t0, t0, 4
	lw t1, 0(t0)
	addi t0, sp, 64
	lw t0, 0(t0)
	add t1, t1, t0
	addi t0, sp, 64
	addi t0, t0, 4
	lw t0, 0(t0)
	add t1, t1, t0
	addi t0, sp, 0
	addi t0, t0, 16
	lw t0, 0(t0)
	add t0, t1, t0
	mv a0, t0
	ld ra, 96(sp)
	ld s0, 104(sp)
	ld s1, 112(sp)
	addi sp, sp, 128
	ret
	.size	main, .-main

