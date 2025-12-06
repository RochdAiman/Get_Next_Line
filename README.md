get_next_line
Reading a line from a file descriptor, one line at a time - A 42 School project.
Table of Contents

Overview
How It Works
Implementation Strategy
Function Prototype
Compilation
Project Structure
Usage Examples
Testing
Common Issues & Solutions
Bonus Part

Overview
get_next_line is a function that reads a file descriptor and returns a line ending with a newline character (when present). Each call returns the next line until EOF is reached. This project teaches you about static variables, buffer management, and efficient file reading.
How It Works
The function uses a static variable to store leftover data between calls:

Read BUFFER_SIZE bytes from the file descriptor
Store what you read in a static variable
Extract one line (up to \n or EOF)
Save the remaining data for the next call
Return the extracted line

Visual Example
File content: "Hello\nWorld\n42\n"
BUFFER_SIZE: 5

Call 1: Read "Hello" → return "Hello\n"
Call 2: Read "\nWorl" → return "World\n"
Call 3: Read "d\n42\n" → return "42\n"
Call 4: return NULL (EOF)
Implementation Strategy
Step 1: Helper Functions (get_next_line_utils.c)
You'll need utility functions similar to:
csize_t  ft_strlen(const char *s);
char    *ft_strchr(const char *s, int c);
char    *ft_strjoin(char const *s1, char const *s2);
char    *ft_substr(char const *s, unsigned int start, size_t len);
// Add any other helpers you need
```

### Step 2: Core Logic (get_next_line.c)

**Pseudocode approach:**
```
function get_next_line(fd):
    static buffer (preserves data between calls)
    
    if fd is invalid or BUFFER_SIZE <= 0:
        return NULL
    
    # Read from fd until you find '\n' or reach EOF
    while no newline found in buffer:
        read BUFFER_SIZE bytes into temp
        if read error:
            return NULL
        if nothing read (EOF):
            break
        append temp to buffer
    
    # Extract one line from buffer
    if buffer has content:
        find position of '\n'
        extract line (including '\n')
        save remainder back to buffer
        return line
    
    return NULL
Step 3: Key Considerations
Static Variable:
cstatic char *saved = NULL; // Persists between function calls
Reading Loop:

Use read() to get BUFFER_SIZE bytes at a time
Keep reading until you find \n or reach EOF
Append each read to your saved buffer

Line Extraction:

Find the first \n in your buffer
Create a new string from start to \n (inclusive)
Update the static variable with remaining data

Memory Management:

Always free memory you don't need anymore
Update your static variable carefully
Free and set to NULL when done reading

Function Prototype
cchar *get_next_line(int fd);
Parameters:

fd: File descriptor to read from (0 for stdin, or from open())

Return:

Line read (with \n if present)
NULL if nothing left to read or error

Compilation
bash# Mandatory
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c

# Test with different buffer sizes
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 ...

# Bonus
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_bonus_utils.c main.c
```

## Project Structure
```
get_next_line/
├── get_next_line.c          # Main function
├── get_next_line_utils.c    # Helper functions
├── get_next_line.h          # Header file
├── get_next_line_bonus.c    # Bonus: multiple fd support
├── get_next_line_bonus_utils.c
├── get_next_line_bonus.h
└── README.md
get_next_line.h example:
c#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

char    *get_next_line(int fd);
// Your utility functions prototypes
char    *ft_strjoin(char const *s1, char const *s2);
// etc...

#endif
Usage Examples
Example 1: Reading a File
c#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;
    int     line_count;

    fd = open("test.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    
    line_count = 1;
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("Line %d: %s", line_count++, line);
        free(line);
    }
    close(fd);
    return (0);
}
Example 2: Reading from stdin
c#include "get_next_line.h"
#include <stdio.h>

int main(void)
{
    char *line;

    printf("Enter text (Ctrl+D to stop):\n");
    while ((line = get_next_line(0)) != NULL)
    {
        printf("You wrote: %s", line);
        free(line);
    }
    return (0);
}
Example 3: Bonus - Multiple File Descriptors
c#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1, fd2;
    char *line1, *line2;

    fd1 = open("file1.txt", O_RDONLY);
    fd2 = open("file2.txt", O_RDONLY);

    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);
    line1 = get_next_line(fd1);
    line2 = get_next_line(fd2);

    // Should read alternately from both files correctly
    
    close(fd1);
    close(fd2);
    return (0);
}
Testing
Create Test Files
bashecho -e "Line 1\nLine 2\nLine 3" > test.txt
echo -e "A\nB\nC\nD\nE\nF\nG" > test2.txt
echo "No newline at end" > test3.txt
touch empty.txt
Test Cases to Cover

Normal files with multiple lines
Empty files
Files without newline at end
Single character lines
Very long lines (longer than BUFFER_SIZE)
BUFFER_SIZE = 1 (hardest case)
BUFFER_SIZE = 9999 (large buffer)
Binary files
stdin (read from terminal)
Invalid fd (negative, closed, etc.)
Multiple fds simultaneously (bonus)

Quick Test Script
bash#!/bin/bash
for size in 1 10 42 1000 9999; do
    echo "Testing with BUFFER_SIZE=$size"
    cc -Wall -Wextra -Werror -D BUFFER_SIZE=$size get_next_line.c get_next_line_utils.c main.c
    ./a.out
    echo "---"
done
Use Testers

Tripouille/gnlTester
xicodomingues/francinette

Common Issues & Solutions
Issue 1: Memory Leaks
Problem: Not freeing allocated memory properly
Solution:
c// Always free temp variables you don't return
char *temp = malloc(...);
// use temp
free(temp);

// Free and update static variable carefully
free(saved);
saved = new_value;
Issue 2: Segmentation Fault
Common causes:

Accessing NULL pointers
Not checking read() return value
Not checking malloc() return value

Solution: Add protective checks everywhere:
cif (!buffer)
    return (NULL);
if (bytes_read == -1)
{
    free(saved);
    saved = NULL;
    return (NULL);
}
Issue 3: Infinite Loop
Problem: Not handling EOF correctly
Solution: Check if read() returns 0 (EOF) and break the loop
Issue 4: Wrong Output with BUFFER_SIZE=1
Problem: Off-by-one errors, character-by-character reading not handled
Solution: Make sure your logic works for single character reads
Issue 5: Static Variable Not Updating
Problem: Line is returned but leftover data is lost
Solution:
c// After extracting line, update static:
char *new_saved = ft_strdup(saved + newline_position + 1);
free(saved);
saved = new_saved;
Bonus Part
Multiple File Descriptors
The bonus requires handling multiple file descriptors simultaneously:
cstatic char *saved[OPEN_MAX]; // or use fd as index: saved[fd]
// or
static char *saved[1024]; // reasonable limit

// In your function:
char *get_next_line(int fd)
{
    static char *saved[1024];
    
    // Use saved[fd] instead of just saved
    // Each fd gets its own buffer
}
Key points:

Each file descriptor needs its own static buffer
Use an array of static pointers indexed by fd
OPEN_MAX or 1024 is usually sufficient for the array size
Don't forget to handle each fd independently

Allowed Functions

read
malloc
free

Forbidden

Global variables
Libft (must rewrite needed functions)
lseek()
Your own implementations of forbidden functions

Evaluation Tips

Test with valgrind: valgrind --leak-check=full ./a.out
Compile with different BUFFER_SIZE values
Test edge cases during defense
Be ready to explain static variables
Know exactly how your memory management works
