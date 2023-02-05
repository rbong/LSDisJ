# Contributing

## Documenting Callable Addresses

Document subroutines and functions using the following format:

```
;; 00:0000 Description of what the subroutine does.
;; 00:0000
;; 00:0000 Args:
;; 00:0000   arg_name = description of a single-byte argument on the stack
;; 00:0000   word_arg_name (word) = description of a word argument on the stack
;; 00:0000
;; 00:0000 Entry conditions:
;; 00:0000   AF = description of a dual register
;; 00:0000   B = description of a single register
;; 00:0000
;; 00:0000 Exit conditions:
;; 00:0000   DE = contains the result
;; 00:0000
;; 00:0000 Registers used: AF, B, DE
00:0000 call_subroutine
```

Files with external source files should include the path, and indicate if they're modified:

```
;; 00:0000 gbdk 2.95 path/to/file.s:subroutine_name (with modifications)
;; 00:0000
;; 00:0000 Description of what the subroutine does.
;; 00:0000
;; 00:0000 Exit conditions:
;; 00:0000   DE = contains the result
;; 00:0000
;; 00:0000 Registers used: AF, B, DE
00:0000 subroutine_name
```

C functions should include the function definition:

```
;; 00:0000 gbdk 2.95 path/to/file.c:function_name
;; 00:0000
;; 00:0000 int my_fn(char arg)
;; 00:0000
;; 00:0000 Description of what the function does.
;; 00:0000
;; 00:0000 Result:
;; 00:0000   DE = description of value
00:0000 function_name
```

Simple/short subroutines can condense sections down to one line:

```
;; 00:0000 Description of what the subroutine does.
;; 00:0000 Args: arg_name, word_name (word)
;; 00:0000 Entry conditions: AF = description
;; 00:0000 Exit conditions: DE = result
;; 00:0000 Registers used: AF, B, DE
00:0000 call_subroutine
```

## Internal Tools

### Prerequisites

  - [Python](https://www.python.org/)

### Setup

```bash
pip3 install .
```

### Usage

Search for bytes from one ROM in another:

```bash
python3 -m lsdisj.grep src/lsdj-8.5.1.gb:01:4200 src/lsdj-9.2.L.gb:01:0000
```

Get statistics about unknown calls:

```bash
python3 -m lsdisj.stats build/9.2.L/src/bank_*.asm
```

## Vim Plugin

Sets up LSDisJ windows, functions, commands, and bindings in Vim.

### Setup

In `.vimrc`:

```vim
" Loads the LSDisJ plugin on running :Lsdisj
command Lsdisj exec 'source ~/prog/personal/lsdisj/plugin/lsdisj.vim | Lsdisj'
```

### Usage

Launch:

```vim
Lsdisj
```

Opens one tab with stats and excluded stats,
a tab with the bank `.asm` file and the `.sym` file,
and a tab with the `.inc` file.

Edit the excluded stats to excluded functions from stats.
Each line is regex-based: start lines with `$` for comments.

Open a bank file:

```vim
" Defaults to bank 0
" Binding: <leader>lb
LsdisjBank [bank]
```

Make:

```vim
" Binding: <leader>lm
LsdisjMake [...args]
```

Compile stats:

```vim
" Binding: <leader>ls
LsdisjStats
```

Jump to address under cursor:

```vim
" Binding: <leader>lm
LsdisjJump
```

If the cursor is in the stats window or the sym window, jumps to the bank window.
If the cursor is in the bank window, jumps to the sym window.

Leave a comment/label at the address under cursor:

```vim
" Binding: <leader>lc
LsdisjComment
" Binding: <leader>ll
LsdisjLabel
```

Works from the sym and bank window.

Yank the address under the cursor:

```vim
" Binding: <leader>ly
LsdisjYank
```

Yanks the bank to `@b`, the address to `@a`, the full address to `@f`/`@"`,
a generic call label to `@c`, and a generic data label to `@d`.
