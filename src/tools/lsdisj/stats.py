import argparse
import re
import sys

# Define args

parser = argparse.ArgumentParser(
    prog='python3 -m lsdisj.stats',
    description='Get decompilation stats from asm files.',
)

parser.add_argument(
    '-r',
    '--recursive',
    action='store_true',
    help='Calculate references for functions recursively.'
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

def is_unknown_fn(fn):
    return bool(re.search('^call_[0-9a-f]{2}_[0-9a-f]{4}$', fn))

for filename in files:
    current_fn = None
    is_unknown = False
    calls = None
    unk_addrs = None
    unk_bytes = None

    for line in open(filename, 'r', encoding='utf-8').readlines():
        # Skip empty lines
        if re.match('^ *$', line):
            continue

        # Skip comments
        if re.match('^ *;', line):
            continue

        # Skip non-function labels
        if re.match('^(jump|jp|jr|data|kit)_.*:$', line):
            continue

        # Skip local labels
        if re.match('^\.', line):
            continue

        # Skip data
        if re.match('^ *d[sb] ', line):
            continue

        # Parse label
        label_match = re.match('^ *([^ ;]+):$', line)
        if label_match:
            fn = label_match[1]
            current_fn = fn
            fn_lines[fn] = 0
            is_unknown = is_unknown_fn(label_match[1])
            total_fns += 1
            calls = set()
            fn_calls[fn] = calls

            if is_unknown:
                unk_addrs = {}
                unk_bytes = {}

                fn_unk_addrs[fn] = unk_addrs
                fn_unk_bytes[fn] = unk_bytes
                fn_end[fn] = False
                total_unknown_fns += 1

            continue

        # Skip non-function lines
        if not current_fn:
            continue

        # Update lines
        total_lines += 1
        fn_lines[current_fn] += 1
        if is_unknown:
            total_unknown_lines += 1

        if is_unknown:
            # Check for return instructions at end
            if re.match('^ *reti?( *;|$)', line):
                fn_end[current_fn] = True
                continue
            else:
                fn_end[current_fn] = False

            # Check for unknown addresses/bytes
            match = re.search('\$[0-9a-f]{4}', line)
            if match:
                unk_addrs[match[0]] = True
                continue
            match = re.search('\$[0-9a-f]{2}', line)
            if match:
                unk_bytes[match[0]] = True
                continue

        # Parse all unknown call refs
        for ref in re.findall('call_[0-9a-f_]*', line):
            total_refs += 1
            if is_unknown_fn(ref):
                total_unknown_refs += 1
                if ref not in calls:
                    if ref not in fn_refs:
                        fn_refs[ref] = set()
                    fn_refs[ref].add(current_fn)
                    # Record call
                    if is_unknown:
                        calls.add(ref)

# Remove empty functions

for fn, lines in fn_lines.items():
    if lines == 0:
        if fn in fn_refs:
            del fn_refs[fn]
        total_fns -= 1

# Get recursive refs

if args.recursive:
    recursive_refs = {}
    def get_recursive_refs(fn, visited):
        if fn in visited:
            return 0
        visited.add(fn)

        if fn in recursive_refs:
            return recursive_refs[fn]
        if fn not in fn_refs:
            recursive_refs[fn] = 0
            return 0

        count = 0
        for caller in fn_refs[fn]:
            count += 1 + get_recursive_refs(caller, visited)

        recursive_refs[fn] = count
        return count

    for fn, refs in fn_refs.items():
        get_recursive_refs(fn, set())

    fn_refs = recursive_refs

# Sort statistics

stats = [
    (
        -fn_end.get(fn, False),
        len(fn_calls.get(fn, {})),
        len(fn_unk_addrs.get(fn, {})),
        len(fn_unk_bytes.get(fn, {})),
        -refs if args.recursive else -len(refs),
        fn_lines.get(fn, 0),
        fn
    )
    for fn, refs
    in fn_refs.items()
    if is_unknown_fn(fn)
]

# Print statistics

for end, calls, addrs, bytes, refs, lines, fn in sorted(stats):
    print(f'{fn} ends: {"yes" if end else "no "}   unk. calls: {calls: <4} unk. addrs: {addrs: <4} unk. bytes: {bytes: <4} refs: {-refs: <4} lines: {lines}')

total_known_fns = total_fns - total_unknown_fns
total_known_refs = total_refs - total_unknown_refs
total_known_lines = total_lines - total_unknown_lines

print('---')
print(f'total functions:  {total_fns}')
print(f'total references: {total_refs}')
print(f'total lines:      {total_lines}')
print('---')
print(f'total unknown functions:  {total_unknown_fns}')
print(f'total unknown references: {total_unknown_refs}')
print(f'total unknown lines:      {total_unknown_lines}')
print('---')
print(f'total known functions:  {total_known_fns:<5} / {total_fns:<5} [{total_known_fns / total_fns:.2%}]')
print(f'total known references: {total_known_refs:<5} / {total_refs:<5} [{total_known_refs / total_refs:.2%}]')
print(f'total known lines:      {total_known_lines:<5} / {total_lines:<5} [{total_known_lines / total_lines:.2%}]')
