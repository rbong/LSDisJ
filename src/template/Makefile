# Options

# Verify the ROM is correct after building
VERIFY := true

# Assembler program
ASM := rgbasm
# Assembler flags
ASFLAGS := -L

# Linker program
LD := rgblink
# Linker flags
LDFLAGS := -w -m src/lsdj.map

# Image converter program
GFX := rgbgfx
# Image converter flags
GFXFLAGS :=

# ROM checksum fixer program
FIX := rgbfix
# ROM checksum fixer flags
FIXFLAGS := \
	--validate \
	--pad-value 0xFF

# Helper variables

IMAGE_TARGETS = \
	src/gfx/font_1_content.2bpp \
	src/gfx/font_2_content.2bpp \
	src/gfx/font_3_content.2bpp \
	src/gfx/tileset.2bpp

# Special targets

.PHONY: default clean

# Build targets

%.2bpp: %.png
	$(GFX) $(GFXFLAGS) -o "$@" "$<"

src/lsdj.o: src/lsdj.asm $(wildcard src/bank_*.asm) $(wildcard src/*.inc) $(IMAGE_TARGETS)
	$(ASM) $(ASFLAGS) -i src -o "$@" "$<"

lsdj.gb: src/lsdj.o
	$(LD) $(LDFLAGS) -o "$@" "$<"
	$(FIX) $(FIXFLAGS) "$@"
ifeq ($(VERIFY),true)
	md5sum -c lsdj.gb.md5 < "$@"
endif

# Phony targets

default: lsdj.gb

clean:
	rm -f src/*.o src/gfx/*.2bpp src/lsdj.map lsdj.gb
