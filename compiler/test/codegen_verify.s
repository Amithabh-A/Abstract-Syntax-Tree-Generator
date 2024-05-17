	.file	1 "codegen_verify.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.globl	array
	.section	.bss,"aw",@nobits
	.align	2
	.type	array, @object
	.size	array, 40
array:
	.space	40
	.globl	key
	.align	2
	.type	key, @object
	.size	key, 4
key:
	.space	4
	.globl	mid
	.align	2
	.type	mid, @object
	.size	mid, 4
mid:
	.space	4
	.globl	temp
	.align	2
	.type	temp, @object
	.size	temp, 4
temp:
	.space	4
	.globl	test
	.align	2
	.type	test, @object
	.size	test, 4
test:
	.space	4
	.globl	i
	.align	2
	.type	i, @object
	.size	i, 4
i:
	.space	4
	.globl	result
	.align	2
	.type	result, @object
	.size	result, 4
result:
	.space	4
	.globl	start
	.align	2
	.type	start, @object
	.size	start, 4
start:
	.space	4
	.globl	e
	.align	2
	.type	e, @object
	.size	e, 4
e:
	.space	4
	.text
	.align	2
	.globl	main
	.set	nomips16
	.set	nomicromips
	.ent	main
	.type	main, @function
main:
	.frame	$fp,8,$31		# vars= 0, regs= 1/0, args= 0, gp= 0
	.mask	0x40000000,-4
	.fmask	0x00000000,0
	.set	noreorder
	.set	nomacro
	addiu	$sp,$sp,-8
	sw	$fp,4($sp)
	move	$fp,$sp
	move	$2,$0
	move	$sp,$fp
	lw	$fp,4($sp)
	addiu	$sp,$sp,8
	jr	$31
	nop

	.set	macro
	.set	reorder
	.end	main
	.size	main, .-main
	.ident	"GCC: (Ubuntu 10.5.0-4ubuntu2) 10.5.0"
	.section	.note.GNU-stack,"",@progbits
