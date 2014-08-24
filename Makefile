BIN := halt
LDSCRIPT := build/stm32_flash.ld
OBJS := boot/startup_stm32f4xx.o kern/halt.o

vpath %.o boot:kern

PREFIX := arm-none-eabi-
AS := $(PREFIX)as
CC := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump

LDFLAGS := -T $(LDSCRIPT)

$(BIN): $(OBJS)

clean:
	$(RM) $(OBJS)
distclean: clean
	$(RM) $(BIN) $(BIN).d $(BIN).t

%.d: %
	$(OBJDUMP) -d $< >$@
%.t: %
	$(OBJDUMP) -t $< >$@
