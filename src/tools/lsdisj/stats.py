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

fn_calls = {}
fn_lines = {}
fn_end = {}
fn_refs = {}
fn_lines = {}

for filename in files:
    current_fn = None
    is_unknown = False
    calls = None

    for line in open(filename, 'r', encoding='utf-8').readlines():
        # Parse label
        label_match = re.match('^(call|data)_(.*):$', line)
        if label_match:
            if label_match[1] == 'call':
                # Handle call label
                fn = label_match[0][:-1]
                current_fn = fn
                is_unknown = bool(re.match('^[0-9a-f]{2}_[0-9a-f]{4}$', label_match[2]))
                if is_unknown:
                    calls = {}
                    fn_calls[fn] = calls
                    fn_lines[fn] = 0
                    fn_end[fn] = False
            elif label_match[1] == 'data':
                # Handle data label
                current_fn = None
                is_unknown = False
                calls = None
            continue

        # Skip non-function lines
        if not current_fn:
            continue

        # Update lines
        if is_unknown:
            fn_lines[current_fn] += 1

        # Handle return function
        if re.match('^ *ret( *;|$)', line):
            if is_unknown:
                fn_end[current_fn] = True
            current_fn = None
            is_unknown = False
            calls = None
            lines = None
            continue

        # Parse all unknown call refs
        for ref in re.findall('call_[a-f0-9]{2}_[a-f0-9]{4}', line):
            # Record ref
            fn_refs[ref] = fn_refs.get(ref, 0) + 1
            # Record call
            if is_unknown:
                calls[ref] = True

# Sort statistics

stats = [
    (-fn_end.get(fn, False), len(fn_calls.get(fn, {})), -refs, fn_lines.get(fn, 0), fn)
    for fn, refs
    in fn_refs.items()
]

# Print statistics

for end, calls, refs, lines, fn in sorted(stats):
    print(f'{fn}:\tends: {"yes" if end else "no"}\tunknown calls: {calls}\treferences: {-refs}\tlines: {lines}')
