#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_DISPLAY_LENGTH 100
#define MAXIMUM_COMMAND 100

// Declare the function prototypes before main
int take_cmd(char *prmpt);
void exec_prmpt(char *command_line);

int main()
{
    char prmpt[MAX_DISPLAY_LENGTH];
    while (1)
    {
        write(STDOUT_FILENO, ":) ", 3); // Display a smiley face
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

void exec_prmpt(char *command_line)
{
    // Check if the command is specified with an absolute path
    if (command_line[0] == '/')
    {
        char *args[MAXIMUM_COMMAND];
        args[0] = command_line; // Use the absolute path as the command
        args[1] = NULL;         // Null-terminate the argument list

        pid_t child_processid = fork();
        if (child_processid < 0)
        {
            perror("Fork Failed");
            exit(1);
        }
        else if (child_processid == 0)
        {
            // Execute the command in the child process
            if (execv(args[0], args) < 0)
            {
                // Print an error message if execution fails
                perror("Execution error");
                exit(1);
            }
        }
        else
        {
            int report;
            waitpid(child_processid, &report, 0);
        }
    }
    else
    {
        // Tokenize the command_line into command and arguments
        char *args[MAXIMUM_COMMAND];
        int arg_count = 0;
        char *token = strtok(command_line, " ");

        while (token != NULL && arg_count < MAXIMUM_COMMAND - 1)
        {
            args[arg_count++] = token;
            token = strtok(NULL, " ");
        }

        args[arg_count] = NULL; // Null-terminate the argument list

        // Check if the command exists in PATH
        char *cmd_path = args[0];
        char *path = getenv("PATH");
        char *path_token = strtok(path, ":");
        char full_path[MAX_DISPLAY_LENGTH];
        int command_found = 0;

        while (path_token != NULL)
        {
            strcpy(full_path, path_token);
            strcat(full_path, "/");
            strcat(full_path, cmd_path);

            if (access(full_path, X_OK) == 0)
            {
                command_found = 1;
                break;
            }

            path_token = strtok(NULL, ":");
        }

        if (command_found)
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
                if (execv(full_path, args) < 0)
                {
                    // Print an error message if execution fails
                    perror("Execution error");
                    exit(1);
                }
            }
            else
            {
                int report;
                waitpid(child_processid, &report, 0);
            }
        }
        else
        {
            // Print an error message if the command is not found
            fprintf(stderr, "Command not found: %s\n", cmd_path);
        }
    }
}

