	.file	1 "test1.c"
	.section .mdebug.abi32
	.previous
	.nan	legacy
	.module	fp=xx
	.module	nooddspreg
	.abicalls
	.text
	.globl	a
	.section	.bss,"aw",@nobits
	.align	2
	.type	a, @object
	.size	a, 4
a:
	.space	4
	.globl	b
	.align	2
	.type	b, @object
	.size	b, 4
b:
	.space	4
	.globl	c
	.align	2
	.type	c, @object
	.size	c, 4
c:
	.space	4
	.globl	d
	.align	2
	.type	d, @object
	.size	d, 4
d:
	.space	4
	.globl	e
	.align	2
	.type	e, @object
	.size	e, 4
e:
	.space	4
	.globl	f
	.align	2
	.type	f, @object
	.size	f, 4
f:
	.space	4
	.globl	g
	.align	2
	.type	g, @object
	.size	g, 4
g:
	.space	4
	.globl	h
	.align	2
	.type	h, @object
	.size	h, 4
h:
	.space	4
	.globl	i
	.align	2
	.type	i, @object
	.size	i, 4
i:
	.space	4
	.globl	j
	.align	2
	.type	j, @object
	.size	j, 4
j:
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
	lui	$2,%hi(a)
	lw	$3,%lo(a)($2)
	lui	$2,%hi(b)
	lw	$2,%lo(b)($2)
	addu	$3,$3,$2
	lui	$2,%hi(c)
	lw	$2,%lo(c)($2)
	addu	$3,$3,$2
	lui	$2,%hi(d)
	lw	$2,%lo(d)($2)
	addu	$3,$3,$2
	lui	$2,%hi(j)
	sw	$3,%lo(j)($2)
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
