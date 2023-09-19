#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_DISPLAY_LENGTH 100
#define MAXIMUM_COMMAND 100

// Declare the function prototypes before main
int take_cmd(char *prmpt);
void exec_prmpt(char *command);

int main()
{
    char prmpt[MAX_DISPLAY_LENGTH];
    while (1)
    {
        write(STDOUT_FILENO, "#cisfun$ ", 9);
        if (take_cmd(prmpt) == 0)
        {
            continue;
        }

        // Remove the trailing newline character
        prmpt[strlen(prmpt) - 1] = '\0';

        if (strcmp(prmpt, "exit") == 0)
        {
            // Exit the shell if the user enters "exit"
            break;
        }

        exec_prmpt(prmpt);
    }

    return 0;
}

int take_cmd(char *prmpt)
{
    ssize_t size_ofchar_read = read(STDIN_FILENO, prmpt, MAX_DISPLAY_LENGTH);
    if (size_ofchar_read < 0)
    {
        perror("Input error");
        exit(1);
    }
    else if (size_ofchar_read == 0)
    {
        // Handle end of file (Ctrl+D)
        write(STDOUT_FILENO, "\n", 1);
        exit(0);
    }
    prmpt[size_ofchar_read] = '\0';
    return size_ofchar_read;
}

void exec_prmpt(char *command)
{
    pid_t child_processid = fork();
    if (child_processid < 0)
    {
        perror("Fork Failed");
        exit(1);
    }
    else if (child_processid == 0)
    {
        // Execute the command in the child process
        if (execlp(command, command, (char *)NULL) < 0)
        {
            // Print an error message and exit if the executable is not found
            perror("Command not found");
            exit(1);
        }
    }
    else
    {
        int report;
        waitpid(child_processid, &report, 0);
    }
}

