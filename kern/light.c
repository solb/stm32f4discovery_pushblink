#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stm32f4xx.h>

void SystemInit(void) {
	// Clock the GPIO modules we'll be using
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN | RCC_AHB1ENR_GPIOGEN;


	// Tell the NVIC to respond to IRQ 6
	NVIC->ISER[0] |= 1 << /*EXTI0*/6;

	// Attach the USER button's GPIO module to the NVIC's external interrupt line
	SYSCFG->EXTICR[1] &= /*low-order (external interrupt line 0) from source 0 (module A)*/0xfff0;

	// Enable falling-edge (button release) triggered events on external interrupt line 0
	EXTI->RTSR &= /*low-order (external interrupt line 0) ignores rising edge triggers*/0xfffffffe;
	EXTI->FTSR |= /*low-order (external interrupt line 0) catches falling edge triggers*/0x1;
	EXTI->IMR |= /*low-order (external interrupt line 0) interrupts enabled*/0x1;
	EXTI->EMR |= /*low-order (external interrupt line 0) event handling on*/0x1;

	// Set the LED GPIO pins to function as digital outputs
	GPIOG->MODER |= /*dout*/1 << (/*pin 13*/13 * 2) | 1 << (14 * 2);

}

void EXTI0_Handler(void) {
	// Change the LED pattern up!
	static uint16_t combo = 0;
	combo = (combo + 1) % 0x04;
	uint16_t tmp = (GPIOG->ODR & 0x9fff) | combo << /*pins 13 and 14*/13;
	GPIOG->ODR = tmp;

	// Inform the external interrupt controller that we handled the IRQ
	EXTI->PR = /*line 0*/0x1;
}

int main(void) {
	while(true);
}
