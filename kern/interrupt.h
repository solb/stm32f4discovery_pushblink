#ifndef INTERRUPT_H_
#define INTERRUPT_H_

#include <stdint.h>

// Length-8 array
extern uint32_t *const nvic_iser;

// Length-8 array
extern uint32_t *const nvic_icpr;

// Length-8 array
extern uint32_t *const nvic_iabr;

typedef struct {
	uint32_t imr;
	uint32_t emr;
	uint32_t rtsr;
	uint32_t ftsr;
	uint32_t swier;
	uint32_t pr;
} exti_t;

extern exti_t *const exti;

#endif
