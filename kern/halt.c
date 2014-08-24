#include <stdbool.h>

void SystemInit(void) {}

int main(void) {
	register int test = 3;
	while(test)
		--test;
	while(true);
}
