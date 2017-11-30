DIR_TOP = $(abspath .)
DIR_BUILD = $(DIR_TOP)/build

TESTS = $(DIR_BUILD)/test-accumulator
DISASMS = $(DIR_BUILD)/test-accumulator.S

TARGET = riscv64-unknown-elf
CC     = $(TARGET)-gcc
AR     = $(TARGET)-ar
OBJDUMP = $(TARGET)-objdump

CFLAGS = -Wall -O3 -I$(DIR_TOP)

vpath %.c $(DIR_TOP)/src

.SUFFIXES:
.PHONY: all clean disasm

all: $(TESTS)

disasm: $(DISASMS)

$(DIR_BUILD)/%: %.c | $(DIR_BUILD)
	$(CC) $(CFLAGS) $< -o $@ $(LFLAGS)

$(DIR_BUILD)/%.S: $(DIR_BUILD)/%
	$(OBJDUMP) -S $< > $@

$(DIR_BUILD):
	mkdir -p $@

clean:
	rm -rf $(DIR_BUILD)
