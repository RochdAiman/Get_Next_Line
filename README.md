# get_next_line

## Description

**get_next_line** is a C function designed to read a file or an input stream one line at a time. Each call to `get_next_line` returns the next line of input, making it ideal for processing files or input streams in a memory-efficient, controlled manner.

This project is a staple in the 42 cursus and aims to develop robust file I/O and dynamic memory management skills.

## Features

- Reads from any valid file descriptor (including files, `stdin`, etc.).
- Returns the next line from the given descriptor with each call.
- Handles multiple file descriptors simultaneously.
- Efficient memory usage and line buffering.
- Does **not** retain newlines at the end of lines (except as required).

## Usage

### Function Prototype

```c
char *get_next_line(int fd);
```

- **fd**: File descriptor to read from.

### Return Value

- Returns a pointer to the next line read from `fd` (including the newline character if present).
- Returns `NULL` when there is nothing else to read or on error.

### Example

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

## Installation

1. **Clone the repository:**
    ```bash
    git clone https://github.com/<your-username>/get_next_line.git
    cd get_next_line
    ```

2. **Compile the library:**
    ```bash
    make
    ```

    This will generate `get_next_line.a`.

3. **Include the header and link the library in your project:**
    - Add `#include "get_next_line.h"` to your source files.
    - Compile your code with the library, e.g.:
        ```bash
        gcc main.c -L. -lget_next_line
        ```

## Files

- `get_next_line.c` - Main function implementation.
- `get_next_line.h` - Header file with function prototype(s).
- `get_next_line_utils.c` - Helper functions, if any.
- `Makefile` - Compilation recipes.

## Project Constraints

- No use of static or global variables (unless required by subject).
- Memory leaks or invalid reads are **not** allowed.
- Only authorized standard C functions (e.g., `read`, `malloc`, `free`).
- The buffer size is controlled by the `BUFFER_SIZE` macro.

## Testing

- You can test the project with your own files or tools.
- Try varying `BUFFER_SIZE` for robustness.

## Authors

- [Aiman Rochd](https://github.com/RochdAiman)

---

> _Project part of 42 School curriculum._

