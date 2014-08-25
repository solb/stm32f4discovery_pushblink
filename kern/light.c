#include "spec.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void SystemInit(void) {}

void EXTI0_Handler(void) {
	while(true);
}

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
	uint32_t imr;
	uint32_t emr;
	uint32_t rtsr;
	uint32_t ftsr;
	uint32_t swier;
	uint32_t pr;
} exti_t;

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

#define NVIC_ISER0_ACTION  (uint32_t *)0xe000e100
#define PERIPH_BASE        (uint8_t *)0x40000000
#define PERIPH_SYSCFG_BASE (PERIPH_BASE + 0x13800)
#define PERIPH_RCC_BASE    (PERIPH_BASE + 0x23800)
#define PERIPH_EXTI_BASE   (PERIPH_BASE + 0x13c00)
#define PERIPH_GPIOA_BASE  (PERIPH_BASE + 0x20000)
#define PERIPH_GPIOD_BASE  (PERIPH_GPIOA_BASE + 0xc00)

int main(void) {
	puts("primask is:");
	puts(get_primask() ? "ACTIVATED" : "normal");
	puts("faultmask is:");
	puts(get_faultmask() ? "ACTIVATED" : "normal");

	*NVIC_ISER0_ACTION |= 1 << /*EXTI0*/6;

	syscfg_t *syscfg = (syscfg_t *)PERIPH_SYSCFG_BASE;
	syscfg->exticr1 &= /*low-order (external interrupt line 0) from source 0 (module A)*/0xfff0;

	rcc_t *rcc = (rcc_t *)PERIPH_RCC_BASE;
	rcc->ahb1enr |= 1 << /*GPIO module A*/0 | 1 << /*module D*/3;

	exti_t *exti = (exti_t *)PERIPH_EXTI_BASE;
	exti->rtsr &= /*low-order (external interrupt line 0) ignores rising edge triggers*/0xfffffffe;
	exti->ftsr |= /*low-order (external interrupt line 0) catches falling edge triggers*/0x1;
	exti->imr |= /*low-order (external interrupt line 0) interrupts enabled*/0x1;
	exti->emr |= /*low-order (external interrupt line 0) event handling on*/0x1;

	gpio_t *gpioa = (gpio_t *)PERIPH_GPIOA_BASE;
	gpio_t *gpiod = (gpio_t *)PERIPH_GPIOD_BASE;
	gpiod->moder |= /*dout*/1 << (/*pin 13*/13 * 2) | 1 << (14 * 2) | 1 << (12 * 2) | 1 << (15 * 2);

	while(true) {
		for(uint16_t combo = 0; combo <= 0xf; ++combo) {
			uint16_t tmp = (gpiod->odr & 0x0fff) | combo << /*pins 12 and up*/12;
			gpiod->odr = tmp;
			while(!(gpioa->idr & 0x1));
			while(gpioa->idr & 0x1);
		}
	}
}
