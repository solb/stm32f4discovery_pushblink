.globl get_primask
.globl get_faultmask

get_primask:
	mrs r0, primask
	bx lr

get_faultmask:
	mrs r0, faultmask
	bx lr
