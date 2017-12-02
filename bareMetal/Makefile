include $(abs_top_srcdir)/Makefrag

tests = \
	accumulator

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

all: $(tests_p)

vpath %.S $(src_dir)

$(PREFIX)-p-%: %.S
	$(CC) $(CFLAGS) -I$(ENV_P) -T$(ENV_P)/link.ld $< $(LFLAGS) -o $@ $(LIBS)

$(PREFIX)-v-%: %.S
	$(CC) $(CFLAGS) -I$(ENV_V) -T$(ENV_V)/link.ld $< $(LFLAGS) -o $@ $(LIBS)

junk += $(tests_p) $(tests_v)
