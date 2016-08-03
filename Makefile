
DIR_TOP = $(abspath .)
DIR_BUILD = $(DIR_TOP)/build
DIR_MAIN = $(DIR_TOP)/src/main/c
DIR_TEST = $(DIR_TOP)/src/test/c

LIBS = $(DIR_BUILD)/librocc.a
TESTS = $(DIR_BUILD)/test-accumulator
DISASMS = $(DIR_BUILD)/test-accumulator.S

RV_NEWLIB = riscv64-unknown-elf
RV_CC     = $(RV_NEWLIB)-gcc
RV_AR     = $(RV_NEWLIB)-ar
RV_OBJDUMP = $(RV_NEWLIB)-objdump

CFLAGS = -Wall -Werror -march=RV64IMAFDXcustom -I$(DIR_MAIN) -I$(DIR_TEST)
LFLAGS = -L$(DIR_BUILD) -lrocc

vpath %.c $(DIR_TOP)/src/main/c
vpath %.c $(DIR_TOP)/src/test/c

.PHONY: all clean disasm

all: $(TESTS)

disasm: $(DISASMS)

$(DIR_BUILD)/%.o: %.c | $(DIR_BUILD)
	$(RV_CC) $(CFLAGS) -c $< -o $@

$(DIR_BUILD)/librocc.a: $(DIR_BUILD)/accumulator.o $(DIR_BUILD)/translator.o
	$(RV_AR) rcs $@ $^

$(DIR_BUILD)/%: %.c $(LIBS)
	$(RV_CC) $(CFLAGS) $< -o $@ $(LFLAGS)

$(DIR_BUILD)/%.S: $(DIR_BUILD)/%
	$(RV_OBJDUMP) -S $< > $@

$(DIR_BUILD):
	mkdir -p $@

clean:
	rm -rf $(DIR_BUILD)
