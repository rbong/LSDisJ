# LSDisJ

Disassembly of [Little Sound DJ](https://www.littlesounddj.com/lsd/index.php).

This currently supportes the last 2 stable versions at the time of writing:

- `9.2.L` (default) (incomplete)
- `8.5.1` (incomplete)

## Prerequisites

- [Git](https://git-scm.com/downloads)
- An LSDj ROM, for example [version 9.2.L](https://www.littlesounddj.com/lsd/latest/rom_images/stable/lsdj9_2_L-stable.zip)
  - Read [the LSDj license](https://www.littlesounddj.com/lsd/latest/rom_images/LICENSE.txt)
  - Extract and move the ROM to `src/lsdj-9.2.L.gb`
- [LuaJIT](https://luajit.org/luajit.html) or [Lua 5.1](https://www.lua.org/start.html#installing)
- [rgbds](https://github.com/gbdev/rgbds)

## Usage

```bash
# Install
git clone --recursive https://github.com/rbong/LSDisJ

# Update
git pull && git submodule update

# Create build/9.2.L/src/lsdj.asm
# Same as "make VERSION=9.2.L"
make

# Remove everything
make clean
```

## External Links

### Reference

- [Pan Docs](https://gbdev.io/pandocs/) (GameBoy development reference, can be used to look up registers, etc.)
- [rgbasm Language Documentation](https://rgbds.gbdev.io/docs/v0.5.1/rgbasm.5) (can be used to look up assembly syntax, expressions, instructions)
- [gbdk 2.95 source](https://github.com/rbong/gbdk/tree/master/gbdk-2.95) (GameBoy development library used by LSDj, with modifications)
- [gbdk 2.95 docs](https://rbong.github.io/gbdk/gbdk-doc-2.95/html/index.html)
- [Awesome Game Boy Development list](https://github.com/gbdev/awesome-gbdev) (Game Boy development resources)

### Development Utilities

- [Emulicious](https://emulicious.net/) (can be used for debugging)

### Other Tools

- [LSDPatcher](https://github.com/jkotlinski/lsdpatch) (can be used to patch kits, palettes, and fonts)
