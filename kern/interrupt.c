#include "interrupt.h"

#include "stm32f4_scoped.h"
uint32_t *const nvic_iser = NVIC_ISER_BASE;
exti_t *const exti = (exti_t *)PERIPH_EXTI_BASE;
#include "stm32f4_scoped.h"
