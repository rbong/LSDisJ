import argparse
import re
import sys

# Define args

parser = argparse.ArgumentParser(
    prog='python3 -m lsdisj.stats',
    description='Get decompilation stats from asm files.',
)

parser.add_argument(
    'files',
    metavar='file',
    nargs='+',
    help='The files to collect statistics on.',
)

# Parse args

def usage_error(msg=''):
    if msg:
        print(msg, file=sys.stderr)
    parser.print_usage(file=sys.stderr)
    sys.exit(1)

args = parser.parse_args()

files = args.files

# Read files

total_fns = 0
total_refs = 0
total_lines = 0
total_unknown_fns = 0
total_unknown_refs = 0
total_unknown_lines = 0

fn_calls = {}
fn_unk_addrs = {}
fn_unk_bytes = {}
fn_lines = {}
fn_end = {}
fn_refs = {}
fn_lines = {}

def is_unknown_fn(call_suffix):
    return bool(re.match('^[0-9a-f]{2}_[0-9a-f]{4}$', call_suffix))

for filename in files:
    current_fn = None
    is_unknown = False
    calls = None
    unk_addrs = None
    unk_bytes = None

    for line in open(filename, 'r', encoding='utf-8').readlines():
        # Parse label
        label_match = re.match('^(call|data)_(.*):$', line)
        if label_match:
            if label_match[1] == 'call':
                # Handle call label

                fn = label_match[0][:-1]
                current_fn = fn
                is_unknown = is_unknown_fn(label_match[2])
                total_fns += 1

                if is_unknown:
                    calls = {}
                    unk_addrs = {}
                    unk_bytes = {}

                    fn_calls[fn] = calls
                    fn_unk_addrs[fn] = unk_addrs
                    fn_unk_bytes[fn] = unk_bytes
                    fn_lines[fn] = 0
                    fn_end[fn] = False
                    total_unknown_fns += 1

            elif label_match[1] == 'data':
                # Handle data label

                current_fn = None
                is_unknown = False
                calls = None
                unk_addrs = None
                unk_bytes = None

            continue

        # Skip non-function lines
        if not current_fn:
            continue

        # Skip empty lines
        if re.match('^ *$', line):
            continue

        # Skip comments
        if re.match('^ *;', line):
            continue

        # Update lines
        total_lines += 1
        if is_unknown:
            fn_lines[current_fn] += 1
            total_unknown_lines += 1

        # Handle return function
        if re.match('^ *ret( *;|$)', line):
            if is_unknown:
                fn_end[current_fn] = True
            current_fn = None
            is_unknown = False
            calls = None
            unk_addrs = None
            unk_bytes = None
            continue

        # Check for unknown addresses/bytes
        if is_unknown:
            match = re.search('\$[0-9a-f]{4}', line)
            if match:
                unk_addrs[match[0]] = True
                continue
            match = re.search('\$[0-9a-f]{2}', line)
            if match:
                unk_bytes[match[0]] = True
                continue

        # Parse all unknown call refs
        for ref in re.findall('call_([0-9a-f_]*)', line):
            total_refs += 1
            if is_unknown_fn(ref):
                # Repair ref
                ref = f'call_{ref}'
                # Record ref
                fn_refs[ref] = fn_refs.get(ref, 0) + 1
                total_unknown_refs += 1
                # Record call
                if is_unknown:
                    calls[ref] = True

# Sort statistics

stats = [
    (
        -fn_end.get(fn, False),
        len(fn_calls.get(fn, {})),
        len(fn_unk_addrs.get(fn, {})),
        len(fn_unk_bytes.get(fn, {})),
        -refs,
        fn_lines.get(fn, 0),
        fn
    )
    for fn, refs
    in fn_refs.items()
]

# Print statistics

for end, calls, addrs, bytes, refs, lines, fn in sorted(stats):
    print(f'{fn} ends: {"yes" if end else "no "}   unk. calls: {calls: <4} unk. addrs: {addrs: <4} unk. bytes: {bytes: <4} refs: {-refs: <4} lines: {lines}')

print(f'total functions: {total_fns}')
print(f'total references: {total_refs}')
print(f'total lines: {total_lines}')
print(f'total unknown functions: {total_unknown_fns}')
print(f'total unknown references: {total_unknown_refs}')
print(f'total unknown lines: {total_unknown_lines}')
