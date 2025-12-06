get_next_line
A C function that reads and returns one line at a time from a file descriptor.
Description
get_next_line reads from a file descriptor and returns one line ending with a newline character. Calling the function repeatedly allows reading a text file line by line until the end.
Function Prototype
cchar *get_next_line(int fd);
Parameters:

fd - File descriptor to read from

Return:

The line read including the \n character (except at EOF without \n)
NULL if there's nothing left to read or an error occurred

File Descriptors (fd)
What is a File Descriptor?
A file descriptor is a non-negative integer that acts as a reference to an open file or input/output resource. The operating system uses it to keep track of open files.
Standard File Descriptors
fdNameDescription0stdinStandard input (keyboard)1stdoutStandard output (screen)2stderrStandard error (screen)
Using File Descriptors
Opening a file:
cint fd;
fd = open("file.txt", O_RDONLY);  // Returns fd (e.g., 3, 4, 5...)
if (fd == -1)
    // Error: file couldn't be opened
Reading from different sources:
c// Reading from a file
int fd = open("text.txt", O_RDONLY);
char *line = get_next_line(fd);
close(fd);

// Reading from standard input (keyboard)
char *line = get_next_line(0);

// Reading from multiple files
int fd1 = open("file1.txt", O_RDONLY);  // fd = 3
int fd2 = open("file2.txt", O_RDONLY);  // fd = 4
char *line1 = get_next_line(fd1);
char *line2 = get_next_line(fd2);
File Descriptor Numbers

File descriptors start at 0 (stdin), 1 (stdout), 2 (stderr)
When you open files, the system assigns the next available number (usually 3, 4, 5...)
Maximum number of open file descriptors is system-dependent (typically 1024)
Each fd maintains its own read position in the file

fd Validation
Your function should handle invalid file descriptors:
c// Invalid cases:
get_next_line(-1);          // Negative fd
get_next_line(1000000);     // fd not opened
get_next_line(closed_fd);   // fd that was already closed
Compilation
bashcc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
The BUFFER_SIZE can be changed during compilation (e.g., -D BUFFER_SIZE=1 or -D BUFFER_SIZE=9999).
Files
Mandatory:

get_next_line.c
get_next_line_utils.c
get_next_line.h

Bonus:

get_next_line_bonus.c
get_next_line_bonus_utils.c
get_next_line_bonus.h

Usage Examples
Example 1: Reading a File
c#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd;
    char *line;

    fd = open("file.txt", O_RDONLY);
    if (fd == -1)
    {
        printf("Error opening file\n");
        return (1);
    }
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
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

    printf("Enter text:\n");
    while ((line = get_next_line(0)) != NULL)  // fd 0 = stdin
    {
        printf("You entered: %s", line);
        free(line);
    }
    return (0);
}
Example 3: Reading Multiple Files (Bonus)
c#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int fd1, fd2, fd3;
    char *line;

    fd1 = open("file1.txt", O_RDONLY);  // fd1 = 3
    fd2 = open("file2.txt", O_RDONLY);  // fd2 = 4
    fd3 = open("file3.txt", O_RDONLY);  // fd3 = 5

    // Read alternately from different files
    line = get_next_line(fd1);  // Line 1 from file1
    printf("fd1: %s", line);
    free(line);

    line = get_next_line(fd2);  // Line 1 from file2
    printf("fd2: %s", line);
    free(line);

    line = get_next_line(fd1);  // Line 2 from file1
    printf("fd1: %s", line);
    free(line);

    line = get_next_line(fd3);  // Line 1 from file3
    printf("fd3: %s", line);
    free(line);

    close(fd1);
    close(fd2);
    close(fd3);
    return (0);
}
Bonus Part
The bonus handles multiple file descriptors simultaneously without losing the reading position of each.
How Bonus Works
c// Instead of one static variable:
static char *buffer;

// Use an array indexed by fd:
static char *buffer[OPEN_MAX];  // or buffer[1024]

// Each fd gets its own buffer:
buffer[fd1] stores data for fd1
buffer[fd2] stores data for fd2
buffer[fd3] stores data for fd3
This allows reading from multiple files in any order while maintaining each file's position:
cget_next_line(3);  // Read from fd 3
get_next_line(5);  // Read from fd 5
get_next_line(3);  // Continue from fd 3 where we left off
get_next_line(4);  // Read from fd 4
get_next_line(5);  // Continue from fd 5 where we left off
Allowed Functions

read - Read from file descriptor
malloc - Allocate memory
free - Free allocated memory

Key Concepts

Static variables to preserve data between function calls
File descriptors as references to open files
Buffer management for efficient reading
Dynamic memory allocation and proper memory management
Multiple fd handling (bonus) using static arrays

Testing
Test your function with:

Different BUFFER_SIZE values (1, 10, 42, 1000, 10000)
Various file types (text files, empty files, files without final newline)
Standard input (fd 0)
Invalid file descriptors (negative numbers, closed fds)
Multiple file descriptors simultaneously (bonus)

bash# Test with different buffer sizes
cc -Wall -Wextra -Werror -D BUFFER_SIZE=1 ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 ...
cc -Wall -Wextra -Werror -D BUFFER_SIZE=9999 ...

# Check for memory leaks
valgrind --leak-check=full ./a.out
