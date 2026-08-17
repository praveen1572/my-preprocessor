# My Preprocessor

A custom C preprocessor implemented in C as part of a C programming project.

## Features

* Removes single-line (`//`) comments.
* Removes multi-line (`/* ... */`) comments.
* Preserves comment-like characters inside string literals.
* Processes `#define` macros.
* Performs object-like macro substitution.
* Processes `#include` directives.
* Supports local header files.
* Supports selected standard headers such as `stdio.h`, `stdlib.h`, and `string.h`.
* Generates a preprocessed `.i` output file.

## Project Structure

```text
my-preprocessor/
├── main.c
├── comments.c
├── includes.c
├── macros.c
├── preprocessor.h
├── myheader.h
├── abc.c
├── abc.i
├── Makefile
└── .gitignore
```

## Build

The project uses GCC and Make.

```cmd
make
```

This generates:

```text
my_Preprocessor.exe
```

## Run

Pass the C source file as an argument:

```cmd
my_Preprocessor abc.c
```

For `abc.c`, the preprocessed output is generated as:

```text
abc.i
```

## Clean

To remove the object files and executable:

```cmd
make clean
```

## Compiler Options

The Makefile uses:

```text
-Wall -Wextra -std=c11 -pedantic
```

## Source Files

| File             | Purpose                                   |
| ---------------- | ----------------------------------------- |
| `main.c`         | Main preprocessing flow and file handling |
| `comments.c`     | Comment removal                           |
| `includes.c`     | Header inclusion                          |
| `macros.c`       | Macro storage and substitution            |
| `preprocessor.h` | Shared declarations                       |
| `Makefile`       | Build and clean rules                     |

## Note

This is a learning project and does not implement the complete C preprocessor specification.
