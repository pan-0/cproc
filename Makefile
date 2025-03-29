.POSIX:
.SUFFIXES:
-include config.mk
MANDIR=$(PREFIX)/share/man
BUILDDIR=stage-1

SRC=$(filter-out driver.c, $(wildcard *.c))
OBJ=$(SRC:%.c=$(BUILDDIR)/%.o)

.PHONY: all
all: $(BUILDDIR)/cproc $(BUILDDIR)/cproc-qbe

$(BUILDDIR):
	@mkdir -p $@

$(BUILDDIR)/cproc: $(BUILDDIR)/driver.o $(BUILDDIR)/util.o
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

$(BUILDDIR)/cproc-qbe: $(OBJ)
	$(CC) $(CFLAGS) $^ -o $@ $(LDFLAGS)

config.h:
	./configure

C = $(CC) $(CFLAGS) -c $< -o $@
-include deps.mk

# Make sure stage2 and stage3 binaries are stripped by adding `-s` to
# `LDFLAGS`. Otherwise they will contain paths to object files, which differ
# between stages.

.PHONY: stage2
stage2: all
	$(MAKE) BUILDDIR=stage-2 CC=stage-1/cproc LDFLAGS='$(LDFLAGS) -s'

.PHONY: stage3
stage3: stage2
	$(MAKE) BUILDDIR=stage-3 CC=stage-2/cproc LDFLAGS='$(LDFLAGS) -s'

.PHONY: bootstrap
bootstrap: stage3
	cmp stage-2/cproc stage-3/cproc
	cmp stage-2/cproc-qbe stage-3/cproc-qbe

.PHONY: install
install: all
	mkdir -p $(DESTDIR)$(BINDIR)
	cp $(BUILDDIR)/cproc $(BUILDDIR)/cproc-qbe $(DESTDIR)$(BINDIR)
	mkdir -p $(DESTDIR)$(MANDIR)/man1
	cp cproc.1 $(DESTDIR)$(MANDIR)/man1

.PHONY: clean
clean:
	@rm -rf stage-1 stage-2 stage-3 config.h config.mk
