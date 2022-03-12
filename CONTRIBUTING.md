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
