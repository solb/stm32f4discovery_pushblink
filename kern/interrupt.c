#include "interrupt.h"

#include "stm32f4_scoped.h"
uint32_t *const nvic_iser = NVIC_ISER_BASE;
uint32_t *const nvic_icpr = NVIC_ICPR_BASE;
uint32_t *const nvic_iabr = NVIC_IABR_BASE;
exti_t *const exti = (exti_t *)PERIPH_EXTI_BASE;
#include "stm32f4_scoped.h"
