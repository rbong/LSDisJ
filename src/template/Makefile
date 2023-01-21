# Options

# Verify the ROM is correct after building
VERIFY := true

# Assembler program
ASM := rgbasm
# Assembler flags
ASFLAGS := \
	-h \
	-L \
	--pad-value 0xFF

# Linker program
LD := rgblink
# Linker flags
LDFLAGS := -w -m src/lsdj.map

# ROM checksum fixer program
FIX := rgbfix
# ROM checksum fixer flags
FIXFLAGS := \
	--validate \
	--p 0xFF

# Helper variables

# Special targets

.PHONY: default clean
.PRECIOUS: lsdj.gb

# Phony targets

default: lsdj.gb

clean:
	rm -f src/*.o src/lsdj.map lsdj.gb

# Build targets

src/lsdj.o: src/lsdj.asm src/memory.asm $(wildcard src/bank_*.asm) $(wildcard src/*.inc) $(wildcard src/*.2bpp) $(wildcard src/*.data)
	$(ASM) $(ASFLAGS) -i src -o "$@" "$<"

lsdj.gb: src/lsdj.o
	$(LD) $(LDFLAGS) -o "$@" "$<"
	$(FIX) $(FIXFLAGS) "$@"
ifeq ($(VERIFY),true)
	md5sum -c lsdj.gb.md5 < "$@"
endif
