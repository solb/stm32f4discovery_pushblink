BIN := light
LDSCRIPT := build/gcc.ld
OBJS := boot/startup_ARMCM4.o boot/isr_vector_extended.o kern/light.o kern/spec.o

vpath %.o boot:kern

PREFIX := arm-none-eabi-
AS := $(PREFIX)as
CC := $(PREFIX)gcc
DB := $(PREFIX)gdb
OBJCOPY := $(PREFIX)objcopy
OBJDUMP := $(PREFIX)objdump

ARCHFLAGS := -mcpu=cortex-m4 -mfpu=fpv4-sp-d16 -mthumb -mfloat-abi=hard
ASFLAGS := $(ARCHFLAGS)
CFLAGS := $(ARCHFLAGS) -std=c99 -g -Wall -Wextra
LDFLAGS := $(ARCHFLAGS) -specs=rdimon.specs -T$(LDSCRIPT)

$(BIN): $(OBJS)

debug: $(BIN)
	$(DB) -iex "add-auto-load-safe-path .gdbinit" $<

clean:
	$(RM) $(OBJS)
distclean: clean
	$(RM) $(BIN) $(BIN).d $(BIN).t

%.d: %
	$(OBJDUMP) -d $< >$@
%.t: %
	$(OBJDUMP) -t $< >$@
