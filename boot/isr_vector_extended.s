	.section .isr_vector
	.space	20                    /* IRQs 1&ndash;5 are unhandled */
	.long EXTI0_Handler           /* IRQ 6 */
