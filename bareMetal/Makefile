include $(abs_top_srcdir)/Makefrag

tests = \
	accumulator \
	translator

tests_p = $(addprefix $(PREFIX)-p-, $(tests))
tests_v = $(addprefix $(PREFIX)-v-, $(tests))

CFLAGS := $(CFLAGS) \
	-static \
	-mcmodel=medany \
	-fvisibility=hidden \
	-nostdlib \
	-nostartfiles \
	-I$(abs_top_srcdir) \
	-I$(RISCVTOOLS) \
	-DID_STRING=$(ID_STRING)

CFLAGS_V := $(CFLAGS) \
	-std=gnu99 \
	-O2

all: $(tests_p) $(tests_v)

vpath %.S $(src_dir)

$(PREFIX)-p-%: %.S
	$(CC) $(CFLAGS) -I$(ENV_P) -T$(ENV_P)/link.ld $< $(LFLAGS) -o $@

$(PREFIX)-v-%: %.S
	$(CC) $(CFLAGS_V) -DENTROPY=0x$(shell echo $@ | md5sum | cut -c 1-7) -I$(ENV_V) -T$(ENV_V)/link.ld $(ENV_V)/entry.S $(ENV_V)/*.c $< $(LFLAGS) -o $@

junk += $(tests_p) $(tests_v)
