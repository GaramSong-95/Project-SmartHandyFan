	.syntax unified
	.thumb

	.text

	.word	0x20005000
	.word	__start

	.global	__start
  	.type 	__start, %function
__start:

	.extern __RO_LIMIT__
	.extern __RW_BASE__
	.extern __ZI_BASE__
	.extern __ZI_LIMIT__

	ldr		r0, =__RO_LIMIT__
	ldr		r1, =__RW_BASE__
	ldr		r3, =__ZI_BASE__

	cmp		r0, r1
	beq		2f

1:
	cmp		r1, r3
	ittt	lo
	ldrlo	r2, [r0], #4
	strlo	r2, [r1], #4
	blo		1b

2:
	ldr		r1, =__ZI_LIMIT__
	mov		r2, #0x0
3:
	cmp		r3, r1
	itt		lo
	strlo	r2, [r3], #4
	blo		3b

	.extern Main

	bl		Main

	b		.
			
	.end
