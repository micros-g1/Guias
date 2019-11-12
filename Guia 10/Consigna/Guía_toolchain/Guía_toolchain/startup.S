	.cpu cortex-m4

.section .vectors, "a"		/* allocatable */
	.word _sp_init_value
	.word _reset_vector

	.thumb
.section .text

    .align  2
    .thumb_func
    .global _reset_vector
_reset_vector:

	cpsid i

	/* esto podría estar en ASM también */
	bl init
	
	bl main

	b .
