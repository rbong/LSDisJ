# Options

CHECK := true
REBUILD := true

VERSION := 8.5.1

ROM := src/lsdj-$(VERSION).gb

DIS := mgbdis/mgbdis.py
DISFLAGS := --disable-auto-ldh

# Helper variables

SYM = $(patsubst %.gb,%.sym,$(ROM))
CHECKSUMS = $(ROM).md5

# Special targets

.PHONY: default check clean
.PRECIOUS: \
	build/%/src \
	build/%/lsdj.sym \
	build/%/lsdj.gb.md5 \
	build/%/Makefile

# Targets

default: build/$(VERSION)

%.gb:
	# ROM not found.
	# If you are trying to disassemble and official ROM, please download and save it to "$@":
	# https://www.littlesounddj.com/lsd/latest/rom_images/
	exit 1

%.sym:
	# Symbol file not found.
	# Without a symbol file, the disassembly will not contain notation.
	# Make sure there is a corresponding "$(SYM)" file for "$(ROM)".
	exit 1

%.md5:
	# Do nothing if checksums don't exist

check: $(ROM) $(CHECKSUMS)
ifeq ($(CHECK),true)
	md5sum -c "$(CHECKSUMS)" < "$(ROM)"
endif

build/%/Makefile: src/template/Makefile
	mkdir -p "build/$*"
	cp src/template/Makefile "build/$*/Makefile"

build/%/src: $(ROM) $(SYM)
	mkdir -p "build/$*"
	$(DIS) $(DISFLAGS) --output-dir "$@" --overwrite "$<"
	# Get rid of the mgbdis Makefile, we have our own
	rm -rf "$@/Makefile"
	# Rename the main assembly file to be more descriptive
	mv "$@"/game.asm "$@"/lsdj.asm

build/%: check build/%/Makefile build/%/src $(ROM) $(SYM)
	mkdir -p "build/$*"
	cp "$(SYM)" build/"$*"/lsdj.sym
	md5sum < "$(ROM)" > build/"$*"/lsdj.gb.md5
ifeq ($(REBUILD),true)
	cd "$@" && make
endif

clean:
	rm -rf build/
