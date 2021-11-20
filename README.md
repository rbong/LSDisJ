# LSDisJ

Disassembly of [Little Sound DJ](https://www.littlesounddj.com/lsd/index.php).
This currently only targets the latest stable version at the time of writing, `8.5.1`.

## Prerequisites

  - [Git](https://git-scm.com/downloads)
  - [LSDj 8.5.1](https://www.littlesounddj.com/lsd/latest/rom_images/) (download to `path/to/LSDisJ/src/lsdj-8.5.1.gb`)
  - [Python](https://www.python.org/)
  - [rgbds](https://github.com/gbdev/rgbds)

## Usage

```bash
# Install
git clone --recursive https://github.com/rbong/LSDisJ

# Update
git pull && git submodule update

# Create build/8.5.1/src/lsdj.asm
make

# Remove everything
make clean
```

## External Links

### Reference

  - [Pan Docs](https://gbdev.io/pandocs/) (GameBoy development reference, can be used to look up registers, etc.)
  - [gbdk 2.95](https://sourceforge.net/projects/gbdk/files/gbdk-win32/2.95/) (GameBoy development library used by LSDj, with modifications)
  - [Awesome Game Boy Development list](https://github.com/gbdev/awesome-gbdev) (Game Boy development resources)

### Development Utilities

  - [Emulicious](https://emulicious.net/) (can be used for debugging)

### Other Tools

  - [LSDPatcher](https://github.com/jkotlinski/lsdpatch) (can be used to patch kits, palettes, and fonts)
