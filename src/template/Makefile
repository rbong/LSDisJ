# Options

VERIFY := true

ASM := rgbasm
ASFLAGS := -L

LD := rgblink
LDFLAGS := -w -m src/lsdj.map

GFX := rgbgfx
GFXFLAGS :=

FX := rgbfix
FXFLAGS := \
	--validate \
	--pad-value 0xFF

# Helper variables

IMAGE_TARGETS = \
	src/gfx/font_1_content.2bpp \
	src/gfx/font_2_content.2bpp \
	src/gfx/font_3_content.2bpp \
	src/gfx/tileset.2bpp

# Special targets

.PHONY: default clean disassemble
.INTERMEDIATE: mgbdis/disassembly/game.asm

# Targets

default: lsdj.gb

%.2bpp: %.png
	$(GFX) $(GFXFLAGS) -o "$@" "$<"

src/lsdj.o: src/lsdj.asm $(wildcard src/bank_*.asm) $(wildcard src/*.inc) $(IMAGE_TARGETS)
	$(ASM) $(ASFLAGS) -i src -o "$@" "$<"

lsdj.gb: src/lsdj.o
	$(LD) $(LDFLAGS) -o "$@" "$<"
	$(FX) $(FXFLAGS) "$@"
ifeq ($(VERIFY),true)
	md5sum -c lsdj.gb.md5 < "$@"
endif

clean:
	rm -f src/*.o src/gfx/*.2bpp src/lsdj.map lsdj.gb
