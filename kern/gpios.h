#ifndef GPIOS_H_
#define GPIOS_H_

#include <stdint.h>

typedef struct {
	uint32_t moder;
	uint16_t otyper;
	uint16_t : 16;
	uint32_t ospeeder;
	uint32_t pupdr;
	uint16_t idr;
	uint16_t : 16;
	uint16_t odr;
	uint16_t : 16;
	uint32_t bsrr;
	uint16_t lckr;
	uint16_t : 16;
	uint32_t afrl;
	uint32_t afrh;
} gpio_t;

extern gpio_t *const gpioa;
extern gpio_t *const gpiod;

#endif
