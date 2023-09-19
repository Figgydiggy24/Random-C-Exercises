#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_DISPLAY_LENGTH 100

// Declare the function prototypes before main
int displ_prmpt(char *prmpt);
int new_prmpt(void);

int main() 
{
    char display[MAX_DISPLAY_LENGTH] = "#cisfun$ ";
    ssize_t size_ofchar_read;

    while (1) 
    {
	    displ_prmpt(display);

        size_ofchar_read = read(STDIN_FILENO, display, sizeof(display));

        if (size_ofchar_read < 0) {
            perror("INPUT ERROR!");
            exit(1);
        } 
        else if (size_ofchar_read == 0)
         {
            char new_prmpt[] = "\n";
	    write(STDOUT_FILENO, &new_prmpt, 1);
	    exit(0);
	 }
	else
	{
            write(STDOUT_FILENO, "\n", 1);
	    write(STDOUT_FILENO, display, size_ofchar_read);
        }

    }
	 pid_t dip = fork();

        if (dip < 0)
        {
            perror("Fork failed");
            exit(1);
        }
        else if (dip == 0) 
{
	char *token;
	token = strtok(display, " \t\n");

	if (token == NULL)
	{
		exit(0)

        {
		char *arguments[MAX_DISPLAY_LENGTH];
		int v = 0;

		while (token != NULL)
		{
			arguments[v] = token;
			token = strtok(NULL, " \t\n");
			i++;
		}
		arguments[i] = NULL;

           execvp(arguments[0], arguments);
	   {
                perror("execvp");
                exit(1);
	    }
	    else
	    {
            int report;
            waitpid(dip, &report, 0);
	    }
	}
}
    return 0;
}

int new_prmpt(void)
 {
    char prmpt[] = "#cisfun$ ";
    return write(STDOUT_FILENO, prmpt, strlen(prmpt));
 }

int displ_prmpt(char *prmpt) 
{
    return write(STDOUT_FILENO, prmpt, strlen(prmpt));
}
