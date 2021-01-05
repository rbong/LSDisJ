# Options

CHECK := true

DIS := mgbdis/mgbdis.py
DISFLAGS :=

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

.PHONY: all clean disassemble
.INTERMEDIATE: mgbdis/disassembly/game.asm

# Targets

all: lsdj.gb

disassemble: src/lsdj.asm

src/lsdj.gb:
	# Please download LSDj 8.5.1 and save it to src/lsdj.gb:
	# https://www.littlesounddj.com/lsd/latest/rom_images/
	exit 1

%.2bpp: %.png
	$(GFX) $(GFXFLAGS) -o $@ $<

mgbdis/disassembly/game.asm: src/lsdj.gb src/lsdj.sym
	$(DIS) $(DISFLAGS) --output-dir mgbdis/disassembly --overwrite src/lsdj.gb

src/lsdj.asm: mgbdis/disassembly/game.asm $(IMAGE_TARGETS)
	cp -r mgbdis/disassembly/*.asm mgbdis/disassembly/*.inc mgbdis/disassembly/gfx src
	mv src/game.asm src/lsdj.asm

src/lsdj.o: src/lsdj.asm $(wildcard src/bank_*.asm) $(wildcard src/*.inc)
	$(ASM) $(ASFLAGS) -i src -o src/lsdj.o src/lsdj.asm

lsdj.gb: src/lsdj.o
	$(LD) $(LDFLAGS) -o lsdj.gb src/lsdj.o
	$(FX) $(FXFLAGS) lsdj.gb
ifeq ($(CHECK),true)
	md5sum -c lsdj.gb.md5
endif

clean:
	rm -f lsdj.gb src/*.asm src/*.inc src/lsdj.map src/lsdj.o
