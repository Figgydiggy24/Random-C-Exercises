#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/**
*my_strlen - function o calculate length of inout string
*k: a pointer to a constant character
return: will return v on success
*/

size_t my_strlen(const char *k) 
{
    size_t v = 0;
    while (str[v] != '\0') {
        v++;
    }
    return (v);
}

int custom_execvp(const char *file, char *const argv[]) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return -1; // Error
    } else if (pid == 0) {
        // Child process

        // Attempt to execute the specified file
        execvp(file, argv);

        // If execvp fails, report an error
        perror("execvp");
        exit(1); // Error
  } else {
        // Parent process

        int status;
        waitpid(pid, &status, 0);

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            return WEXITSTATUS(status);
        } else {
            // Child process did not exit normally
            return -1; // Errori

