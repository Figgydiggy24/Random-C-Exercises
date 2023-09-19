#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define INITIAL_BUFFER_SIZE 128

// Custom getline function
char *custom_getline(int fd) {
    static char *buffer = NULL;
    static size_t buffer_size = 0;
    static size_t current_position = 0;

    if (buffer == NULL) {
        buffer_size = INITIAL_BUFFER_SIZE;
        buffer = (char *)malloc(buffer_size);
        if (buffer == NULL) {
            perror("Memory allocation error");
            exit(1);
        }
    }

    size_t line_length = 0;
    char *line = NULL;
    int eof = 0;

    while (1) {
        // Check if buffer is full and reallocate if necessary
        if (current_position == buffer_size) {
            buffer_size *= 2;
            buffer = (char *)realloc(buffer, buffer_size);
            if (buffer == NULL) {
                perror("Memory allocation error");
                exit(1);
            }
        }

        // Read a character from the input
        ssize_t bytes_read = read(fd, &buffer[current_position], 1);
        if (bytes_read == -1) {
            perror("Read error");
            exit(1);
        } else if (bytes_read == 0) {
            // End of file
            eof = 1;
            break;
        }

        // Check for newline character
        if (buffer[current_position] == '\n') {
            buffer[current_position + 1] = '\0'; // Null-terminate the line
            line_length = current_position + 1;
            current_position = 0; // Reset the position for the next line
            break;
        }

        current_position++;
    }

    if (line_length > 0) {
        line = (char *)malloc(line_length);
        if (line == NULL) {
            perror("Memory allocation error");
            exit(1);
        }
        strncpy(line, buffer, line_length);
    }

    if (eof && line_length == 0) {
        // No more data to read
        free(buffer);
        buffer = NULL;
        return NULL;
    }

    return line;
}

int main() {
    while (1) {
        char *line = custom_getline(STDIN_FILENO);
        if (line == NULL) {
            break;
        }
        write(STDOUT_FILENO, line, strlen(line));
        free(line);
    }

    return 0;
}

