# Options

CHECK := true
REBUILD := true

VERSION := 8.5.1

ROM := src/lsdj-$(VERSION).gb
CHECKSUM := src/lsdj-$(VERSION).gb.md5
SYM := src/lsdj-$(VERSION).sym

DIS := mgbdis/mgbdis.py
DISFLAGS := --disable-auto-ldh

# Helper variables

DIS_TARGET_PREREQS = build/$(VERSION)/src/lsdj.asm \
										 build/$(VERSION)/Makefile \
										 build/$(VERSION)/lsdj.sym \
										 build/$(VERSION)/lsdj.gb.md5

ifeq ($(CHECK),true)
	DIS_TARGET_PREREQS := check $(DIS_TARGET_PREREQS)
endif

ifeq ($(REBUILD),true)
	DIS_TARGET_PREREQS += rebuild
endif

# Special targets

.PHONY: default check disassemble clean rebuild
.PRECIOUS: build/**

# Placeholder targets

%.gb:
	# ROM file not found at "$@".
	# ROMs can be downloaded here:
	# https://www.littlesounddj.com/lsd/latest/rom_images/
	# After downloading, extract the ROM and save it to "$@".
	# You can also specify a ROM file with "make ROM=path/to/rom.gb".
	exit 1

%.md5:
	# Checksum file not found at "$@".
	# You can specify the checksum file with "make CHECKSUM=path/to/checksum.gb.md5".
	# You can also skip checking the file hash with "make CHECK=false".
	# To generate the checksum file, use "md5sum < path/to/rom.gb > path/to/checksum.gb.md5".
	exit 1

%.sym:
	# Symbols file not found at "$@".
	# Without a symbols file, the disassembly will not contain labels.
	# You can specify the symbols file with "make SYM=path/to/symbols.sym".
	# You can also generate an empty symbols file with "touch path/to/symbols.sym".
	exit 1

# Build targets

build/%/Makefile: src/template/Makefile
	mkdir -p "build/$*"
	cp "$^" "$@"

build/%/src/lsdj.asm: $(ROM) $(SYM)
	mkdir -p "build/$*"
	$(DIS) $(DISFLAGS) --output-dir "build/$*/src" --overwrite "$<"
	# Get rid of the mgbdis Makefile, we have our own
	rm -rf "build/$*/src/Makefile"
	# Rename the main assembly file to be more descriptive
	mv "build/$*/src/game.asm" "$@"

build/%/lsdj.sym: $(SYM)
	mkdir -p "build/$*"
	cp "$^" "build/$*/lsdj.sym"

build/%/lsdj.gb.md5: $(ROM)
	mkdir -p "build/$*"
	md5sum < "$^" > "build/$*/lsdj.gb.md5"

# Phony targets

default: disassemble

check: $(ROM) $(CHECKSUM)
	md5sum -c "$(CHECKSUM)" < "$(ROM)"

disassemble: $(DIS_TARGET_PREREQS)

rebuild: build/$(VERSION)/Makefile
	cd "build/$(VERSION)" && $(MAKE)

clean:
	rm -rf build/
