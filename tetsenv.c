#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_DISPLAY_LENGTH 100
#define MAXIMUM_COMMAND 100

// Custom strlen function
size_t my_strlen(const char *str) {
    size_t length = 0;
    while (str[length] != '\0') {
        length++;
    }
    return length;
}

// Custom strcmp function
int my_strcmp(const char *str1, const char *str2) {
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return (*str1 - *str2);
        }
        str1++;
        str2++;
    }
    return (*str1 - *str2);
}

// Function prototypes
int take_cmd(char *prmpt, char *args[]);
void exec_prmpt(char *command, char *args[]);

int main() {
    char prmpt[MAX_DISPLAY_LENGTH];
    char *args[MAXIMUM_COMMAND];

    while (1) {
        write(STDOUT_FILENO, "#cisfun$ ", 9);
        if (take_cmd(prmpt, args) == 0) {
            continue;
        }

        prmpt[my_strlen(prmpt) - 1] = '\0';

        if (my_strcmp(args[0], "exit") == 0) {
            break;
        }

        exec_prmpt(args[0], args);
    }

    return 0;
}

int take_cmd(char *prmpt, char *args[]) {
    ssize_t size_ofchar_read = read(STDIN_FILENO, prmpt, MAX_DISPLAY_LENGTH);
    if (size_ofchar_read < 0) {
        perror("Input error");
        exit(1);
    } else if (size_ofchar_read == 0) {
        write(STDOUT_FILENO, "\n", 1);
        exit(0);
    }
    prmpt[size_ofchar_read] = '\0';

    // Tokenize the input
    char *token = strtok(prmpt, " \n");
    int i = 0;
    while (token != NULL) {
        args[i++] = token;
        token = strtok(NULL, " \n");
    }
    args[i] = NULL; // Set the last element to NULL to indicate the end of arguments

    return i; // Return the number of arguments
}

void exec_prmpt(char *command, char *args[]) {
    pid_t child_processid = fork();
    if (child_processid < 0) {
        perror("Fork Failed");
        exit(1);
    } else if (child_processid == 0) {
        // Child process
        if (execve(command, args, NULL) < 0) {
            perror("Command not found");
            exit(1);
        }
    } else {
        int report;
        waitpid(child_processid, &report, 0);
    }
}

