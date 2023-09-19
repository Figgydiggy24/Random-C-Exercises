#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>

#define MAX_DISPLAY_LENGTH 100


ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream);

// Function prototypes
int displ_prmpt(const char *prmpt);
int new_prmpt(void);

int main(int argc, char *argv[])
{
    char display[MAX_DISPLAY_LENGTH] = "#cisfun$ ";
    ssize_t size_ofchar_read;

    while (1)
    {
        displ_prmpt(display);

        char *input = NULL;
        size_t input_len = 0;
        size_ofchar_read = custom_getline(&input, &input_len, stdin);

        if (size_ofchar_read < 0)
        {
            perror("INPUT ERROR!");
            free(input);
            exit(1);
        }
        else if (size_ofchar_read == 0)
        {
            free(input);
            char new_prmpt = '\n';
            write(STDOUT_FILENO, &new_prmpt, 1);
            exit(0);
        }

const char *output = "Received input: ";
write(STDOUT_FILENO, output, strlen(output));
write(STDOUT_FILENO, input, strlen(input));
write(STDOUT_FILENO, "\n", 1);
        
free(input);
    }

    return 0;
}

int new_prmpt(void)
{
    const char prmpt[] = "#cisfun$ ";
    return write(STDOUT_FILENO, prmpt, strlen(prmpt));
}

int displ_prmpt(const char *display)
{
    return write(STDOUT_FILENO, display, strlen(display));
}

// Custom getline function
ssize_t custom_getline(char **lineptr, size_t *n, FILE *stream)
{
    size_t pos = 0;
    int ch;

    if (*lineptr == NULL)
    {
        *n = 128;
        *lineptr = (char *)malloc(*n);
        if (*lineptr == NULL)
        {
            return -1;
        }
    }

    while (1)
    {
        ch = fgetc(stream);

        if (ch == EOF)
        {
            if (pos == 0)
            {
                return -1; // No data read
            }
            else
            {
                break;
            }
        }

        if (pos >= *n - 1)
        {
            size_t new_size = *n * 2;
            char *new_ptr = (char *)realloc(*lineptr, new_size);
            if (new_ptr == NULL)
            {
                return -1; // Error in realloc
            }
            *lineptr = new_ptr;
            *n = new_size;
        }

        (*lineptr)[pos++] = ch;

        if (ch == '\n')
        {
            break;
        }
    }

    (*lineptr)[pos] = '\0';
    return pos;
}

