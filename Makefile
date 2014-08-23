BIN := halting_kern
LDSCRIPT := build/stm32_flash.ld
OBJS := boot/startup_stm32f4xx.o kern/halt.o

vpath %.o boot:kern

PREFIX := arm-none-eabi-
AS := $(PREFIX)as
CC := $(PREFIX)gcc
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump

LDFLAGS := -T $(LDSCRIPT)

$(BIN).hex: $(BIN).elf
	$(OBJCOPY) -O ihex $< $@
$(BIN).elf: $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LOADLIBES) $(LDLIBS) -o $(BIN).elf

clean:
	$(RM) $(OBJS) $(BIN).elf
distclean: clean
	$(RM) $(BIN).hex $(BIN).d $(BIN).t

%.d: %.elf
	$(OBJDUMP) -d $< >$@
%.t: %.elf
	$(OBJDUMP) -t $< >$@
