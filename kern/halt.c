#include <stdbool.h>
#include <stdio.h>
#include <string.h>

void SystemInit(void) {}

int main(void) {
	const char literal[] = "This is a sample string.";
	char figurative[sizeof literal];
	strcpy(figurative, literal);
	puts(literal);
	puts(figurative);
	++figurative[0];
	puts(literal);
	puts(figurative);

	while(true);
}
