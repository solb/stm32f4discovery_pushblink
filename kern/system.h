#ifndef SYSTEM_H_
#define SYSTEM_H_

#include <stdint.h>

typedef struct {
	uint32_t memrm;
	uint32_t pmc;
	uint16_t exticr1;
	uint16_t : 16;
	uint16_t exticr2;
	uint16_t : 16;
	uint16_t exitcr3;
	uint16_t : 16;
	uint16_t exticr4;
	uint16_t : 16;
	uint32_t cmpcr;
} syscfg_t;

extern syscfg_t *const syscfg;

#endif
