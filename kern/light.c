#include "clock.h"
#include "gpios.h"
#include "interrupt.h"
#include "system.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

void SystemInit(void) {
	// Clock the GPIO modules we'll be using
	rcc->ahb1enr |= 1 << /*GPIO module A*/0 | 1 << /*module D*/3;

	// Tell the NVIC to respond to IRQ 6
	nvic_iser[0] |= 1 << /*EXTI0*/6;

	// Attach the USER button's GPIO module to the NVIC's external interrupt line
	syscfg->exticr1 &= /*low-order (external interrupt line 0) from source 0 (module A)*/0xfff0;

	// Enable falling-edge (button release) triggered events on external interrupt line 0
	exti->rtsr &= /*low-order (external interrupt line 0) ignores rising edge triggers*/0xfffffffe;
	exti->ftsr |= /*low-order (external interrupt line 0) catches falling edge triggers*/0x1;
	exti->imr |= /*low-order (external interrupt line 0) interrupts enabled*/0x1;
	exti->emr |= /*low-order (external interrupt line 0) event handling on*/0x1;

	// Set the LED GPIO pins to function as digital outputs
	gpiod->moder |= /*dout*/1 << (/*pin 13*/13 * 2) | 1 << (14 * 2) | 1 << (12 * 2) | 1 << (15 * 2);
}

void EXTI0_Handler(void) {
	// Change the LED pattern up!
	static uint16_t combo = 0;
	combo = (combo + 1) % 0x10;
	uint16_t tmp = (gpiod->odr & 0x0fff) | combo << /*pins 12 and up*/12;
	gpiod->odr = tmp;

	// Inform the external interrupt controller that we handled the IRQ
	exti->pr = /*line 0*/0x1;
}

int main(void) {
	while(true);
}
