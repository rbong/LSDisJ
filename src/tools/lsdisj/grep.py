import argparse
import os
import re
import sys

# Define args

parser = argparse.ArgumentParser(
    prog='python3 -m lsdisj.grep',
    description='Search LSDj binaries for matching bytes.',
)

parser.add_argument(
    'source',
    metavar='source:bank:address',
    type=str,
    nargs=1,
    help='The source ROM and address of the data to search for.',
)

parser.add_argument(
    'dest',
    metavar='dest[:bank:address]',
    type=str,
    nargs=1,
    help='The destination ROM and optional start address to search.',
)

# Parse args

def usage_error(msg=''):
    if msg:
        print(msg, file=sys.stderr)
    parser.print_usage(file=sys.stderr)
    sys.exit(1)

args = parser.parse_args()

source_split = args.source[0].split(':')

if len(source_split) != 3:
    usage_error()

source_path, source_bank, source_address = source_split

if not os.path.isfile(source_path):
    usage_error('Source ROM not found.')

if re.fullmatch(r'^[0-9a-fA-F]+$', source_bank) is None:
    usage_error('Source bank is invalid.')

source_bank = int(source_bank, 16)

if source_bank > 0x3f:
    usage_error('Source bank must not exceed 0x3f.')

if re.fullmatch(r'^[0-9a-fA-F]+$', source_address) is None:
    usage_error('Source address is invalid.')

source_address = int(source_address, 16)

if source_address > 0x7fff:
    usage_error('Source address must not exceed 0x7fff.')

if source_bank == 0 and source_address > 0x3fff:
    usage_error('For bank 0, source address must not exceed 0x3fff.')

if source_bank >= 1 and source_address < 0x4000:
    usage_error('For banks 1 and greater, source address must not be under 0x4000.')

if source_bank >= 1:
    source_address -= 0x4000

full_source_address = 0x4000 * source_bank + source_address

dest_split = args.dest[0].split(':')

if len(dest_split) != 1 and len(dest_split) != 3:
    usage_error()

if len(dest_split) == 1:
    dest_path = dest_split[0]
    dest_bank = '0'
    dest_address = '0'

if len(dest_split) == 3:
    dest_path, dest_bank, dest_address = dest_split

if not os.path.isfile(dest_path):
    usage_error('Destination ROM not found.')

if re.fullmatch(r'^[0-9a-fA-F]+$', dest_bank) is None:
    usage_error('Destination bank is invalid.')

dest_bank = int(dest_bank, 16)

if dest_bank > 0x3f:
    usage_error('Destination bank must not exceed 0x3f.')

if re.fullmatch(r'^[0-9a-fA-F]+$', dest_address) is None:
    usage_error('Destination address is invalid.')

dest_address = int(dest_address, 16)

if dest_address > 0x7fff:
    usage_error('Destination address must not exceed 0x7fff.')

if dest_bank == 0 and dest_address > 0x3fff:
    usage_error('For bank 0, destination address must not exceed 0x3fff.')

if dest_bank >= 1 and dest_address < 0x4000:
    usage_error('For banks 1 and greater, destination address must not be under 0x4000.')

if dest_bank >= 1:
    dest_address -= 0x4000

# Compare bytes

source_rom = open(source_path, 'rb')
dest_rom = open(dest_path, 'rb')

best_matching_bytes = 0
best_bank = None
best_address = None

while dest_bank < 0x40:
    while dest_address < 0x4000:
        full_dest_address = 0x4000 * dest_bank + dest_address

        source_rom.seek(full_source_address)
        dest_rom.seek(full_dest_address)

        matching_bytes = 0

        while (
            source_address + matching_bytes < 0x4000
            and dest_address + matching_bytes < 0x4000
            and source_rom.read(1) == dest_rom.read(1)
        ):
            matching_bytes += 1

        if matching_bytes > best_matching_bytes:
            best_bank = dest_bank
            best_address = dest_address
            best_matching_bytes = matching_bytes

        dest_address += 1

    dest_bank += 1
    dest_address = 0

if best_address is None:
    print('Not found.', file=sys.stderr)
    sys.exit(1)

if best_bank > 0:
    best_address += 0x4000

print(f'Found match at {best_bank:02x}:{best_address:02x} (0x{best_matching_bytes:02x} bytes)')
