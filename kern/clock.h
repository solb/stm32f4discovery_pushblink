#ifndef CLOCK_H_
#define CLOCK_H_

#include <stdint.h>

typedef struct {
	uint32_t cr;
	uint32_t pllcfgr;
	uint32_t cfgr;
	uint32_t cir;
	uint32_t ahb1rstr;
	uint32_t ahb2rstr;
	uint32_t ahb3rstr;
	uint32_t : 32;
	uint32_t apb1rstr;
	uint32_t apb2rstr;
	uint32_t : 32;
	uint32_t : 32;
	uint32_t ahb1enr;
	uint32_t ahb2enr;
	uint32_t ahb3enr;
	uint32_t : 32;
	uint32_t apb1enr;
	uint32_t apb2enr;
	uint32_t : 32;
	uint32_t : 32;
	uint32_t ahb1lpenr;
	uint32_t ahb2lpenr;
	uint32_t ahb3lpenr;
	uint32_t : 32;
	uint32_t apb1lpenr;
	uint32_t apb2lpenr;
	uint32_t : 32;
	uint32_t : 32;
	uint32_t bdcr;
	uint32_t csr;
	uint32_t : 32;
	uint32_t : 32;
	uint32_t sscgr;
	uint32_t plli2scfgr;
} rcc_t;

extern rcc_t *const rcc;

#endif
