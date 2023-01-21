# Options

# Root build directory
ROOT_DIR := $(dir $(realpath $(lastword $(MAKEFILE_LIST))))

# Check the hash of the ROM before disassembling
CHECK := true
# Rebuild after disassembling
REBUILD := true

# Specify the version to build
VERSION := 9.2.L

# Path to the ROM file
ROM := src/lsdj-$(VERSION).gb
# Path to the checksum file
CHECKSUM := src/lsdj-$(VERSION).gb.md5
# Path to the symbols file
SYM := src/lsdj-$(VERSION).sym
# Path to the include file
INC := src/lsdj-$(VERSION).inc

# Disassembly program
DIS := beast/bin/beast
# Disassembly flags
DISFLAGS :=

# The Lua program
LUA := luajit
# Flags to pass to Lua when running the disassembler
LUAFLAGS :=
# Custom Lua paths
_LUA_PATH := $(ROOT_DIR)/beast/src/?.lua;$(shell $(LUA) -e "print(package.path)")

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

# Phony targets

default: disassemble

check: $(ROM) $(CHECKSUM)
	md5sum -c "$(CHECKSUM)" < "$(ROM)"

disassemble: $(DIS_TARGET_PREREQS)

rebuild: build/$(VERSION)/Makefile
	cd "build/$(VERSION)" && $(MAKE)

clean:
	rm -rf "build/$(VERSION)"

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

%.inc:
	# Include file not found at "$@".
	# You can specify the include file with "make INC=path/to/include.inc".
	# You can also generate an empty include file with "touch $@".
	exit 1

# Build targets

build/%/Makefile: src/template/Makefile
	mkdir -p "build/$*"
	cp "$^" "$@"

build/%/src/lsdj.asm: $(ROM) $(SYM) $(INC)
	rm -rf \
		"build/$*/src/"*.asm \
		"build/$*/src/"*.inc \
		"build/$*/src/"*.2bpp \
		"build/$*/src/"*.data
	mkdir -p "build/$*/src"
	LUA_PATH="$(_LUA_PATH)" $(LUA) $(LUAFLAGS) $(DIS) \
		--main "lsdj.asm" \
		--symbols "$(SYM)" \
		--include "src/hardware.inc" \
		--include "$(INC)" \
		$(DISFLAGS) \
		"$<" \
		"build/$*/src"

build/%/lsdj.sym: $(SYM)
	mkdir -p "build/$*"
	cp "$^" "build/$*/lsdj.sym"

build/%/lsdj.gb.md5: $(ROM)
	mkdir -p "build/$*"
	md5sum < "$^" > "build/$*/lsdj.gb.md5"
