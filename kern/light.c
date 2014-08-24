#include <stdbool.h>
#include <stdint.h>

void SystemInit(void) {}

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

#define PERIPH_BASE       (uint8_t *)0x40000000
#define PERIPH_RCC_BASE   (PERIPH_BASE + 0x23800)
#define PERIPH_GPIOA_BASE  (PERIPH_BASE + 0x20000)
#define PERIPH_GPIOD_BASE (PERIPH_GPIOA_BASE + 0xc00)

int main(void) {
	rcc_t *rcc = (rcc_t *)PERIPH_RCC_BASE;
	rcc->ahb1enr |= 1 << /*GPIO module A*/0 | 1 << /*module D*/3;
	gpio_t *gpioa = (gpio_t *)PERIPH_GPIOA_BASE;
	gpio_t *gpiod = (gpio_t *)PERIPH_GPIOD_BASE;
	gpiod->moder |= /*dout*/1 << (/*pin 13*/13 * 2) | 1 << (14 * 2) | 1 << (12 * 2) | 1 << (15 * 2);

	while(true) {
		for(uint16_t combo = 0; combo <= 0xf; ++combo) {
			uint16_t tmp = (gpiod->odr & 0x0fff) | (combo << /*pins 12 and up*/12);
			gpiod->odr = tmp;
			while(!(gpioa->idr & 0x1));
			while(gpioa->idr & 0x1);
		}
	}
}
