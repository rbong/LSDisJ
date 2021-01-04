# Options

DIS := mgbdis/mgbdis.py
DISFLAGS :=

ASM := rgbasm
ASFLAGS := -L

LD := rgblink
LDFLAGS := -w -m src/lsdj.map

FX := rgbfix
FXFLAGS := \
	--validate \
	--pad-value 0xFF

# Special targets

.PHONY: all clean disassemble

# Targets

all: lsdj.gb

disassemble: src/lsdj.asm

src/lsdj.gb:
	# Please download LSDj 8.5.1 and save it to src/lsdj.gb:
	# https://www.littlesounddj.com/lsd/latest/rom_images/
	exit 1

mgbdis/disassembly/game.asm: src/lsdj.gb src/lsdj.sym
	$(DIS) $(DISFLAGS) --output-dir mgbdis/disassembly --overwrite src/lsdj.gb

src/lsdj.asm: mgbdis/disassembly/game.asm
	cp mgbdis/disassembly/*.asm mgbdis/disassembly/*.inc src
	mv src/game.asm src/lsdj.asm

src/lsdj.o: src/lsdj.asm $(wildcard src/bank_*.asm) $(wildcard src/*.inc)
	$(ASM) $(ASFLAGS) -i src -o src/lsdj.o src/lsdj.asm

lsdj.gb: src/lsdj.o
	$(LD) $(LDFLAGS) -o lsdj.gb src/lsdj.o
	$(FX) $(FXFLAGS) lsdj.gb
	md5sum -c lsdj.gb.md5

clean:
	rm -f lsdj.gb src/*.asm src/*.inc src/lsdj.map src/lsdj.o
