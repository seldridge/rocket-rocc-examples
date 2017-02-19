
DIR_TOP = $(abspath .)
DIR_BUILD = $(DIR_TOP)/build
DIR_MAIN = $(DIR_TOP)/src/main/c
DIR_TEST = $(DIR_TOP)/src/test/c

TESTS = $(DIR_BUILD)/test-accumulator
DISASMS = $(DIR_BUILD)/test-accumulator.S

RV_NEWLIB = riscv64-unknown-elf
RV_CC     = $(RV_NEWLIB)-gcc
RV_AR     = $(RV_NEWLIB)-ar
RV_OBJDUMP = $(RV_NEWLIB)-objdump

CFLAGS = -Wall -O3 -I$(DIR_MAIN) -I$(DIR_TEST)

vpath %.c $(DIR_TOP)/src/main/c
vpath %.c $(DIR_TOP)/src/test/c

.PHONY: all clean disasm

all: $(TESTS)

disasm: $(DISASMS)

$(DIR_BUILD)/%: %.c | $(DIR_BUILD)
	$(RV_CC) $(CFLAGS) $< -o $@ $(LFLAGS)

$(DIR_BUILD)/%.S: $(DIR_BUILD)/%
	$(RV_OBJDUMP) -S $< > $@

$(DIR_BUILD):
	mkdir -p $@

clean:
	rm -rf $(DIR_BUILD)
