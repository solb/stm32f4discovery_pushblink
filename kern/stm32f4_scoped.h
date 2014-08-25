// Include this header twice from a source file: once to define these scoped
// symbols, and a second time to hide them again.

#ifndef SCOPED_SYMBS_DEFINED_
	#define SCOPED_SYMBS_DEFINED_

	#define NVIC_ISER_BASE     (uint32_t *)0xe000e100
	#define NVIC_ICPR_BASE     (uint32_t *)0xe000e280
	#define NVIC_IABR_BASE     (uint32_t *)0xe000e300
	#define PERIPH_BASE        (uint8_t *)0x40000000
	#define PERIPH_SYSCFG_BASE (PERIPH_BASE + 0x13800)
	#define PERIPH_RCC_BASE    (PERIPH_BASE + 0x23800)
	#define PERIPH_EXTI_BASE   (PERIPH_BASE + 0x13c00)
	#define PERIPH_GPIOA_BASE  (PERIPH_BASE + 0x20000)
	#define PERIPH_GPIOD_BASE  (PERIPH_GPIOA_BASE + 0xc00)

#else
	#undef SCOPED_SYMBS_DEFINED_

	#undef NVIC_ISER0_ACTION
	#undef PERIPH_BASE
	#undef PERIPH_SYSCFG_BASE
	#undef PERIPH_EXTI_BASE
	#undef PERIPH_GPIOA_BASE
	#undef PERIPH_GPIOD_BASE

#endif
