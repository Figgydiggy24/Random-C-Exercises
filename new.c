#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_DISPLAY_LENGTH 100
#define MAXIMUM_COMMAND 100

// Declare the function prototypes before main
int take_cmd(char *prmpt);
void parse_prmpt(char *prmpt, char **command);
char *concatenate_strings(char *destination, const char *source);
void exec_prmpt(char **command);
char *myown_strcat(char *dest, const char *src);

char *concatenate_strings(char *destination, const char *source)
{
char *ptr = destination;
    while (*ptr != '\0')
    {
        ptr++;
    }
    while (*source != '\0')
    {
        *ptr++ = *source++;
    }
    *ptr = '\0';
    return destination;
}

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
		char *command[MAXIMUM_COMMAND];
		parse_prmpt(prmpt, command);
		
		if (command[0] != NULL)
		{
			exec_prmpt(command);
		}
	}
	return 0;
}

int take_cmd(char *prmpt)
{
	ssize_t size_ofchar_read = read(STDIN_FILENO, prmpt, MAX_DISPLAY_LENGTH);
	if(size_ofchar_read < 0)
	{
		perror("Input error");
		exit(1);
	}
	else if (size_ofchar_read == 0)
	{
		exit(0);
	}
	prmpt[size_ofchar_read] = '\0';
	return size_ofchar_read;
}

void parse_prmpt(char *prmpt, char **command)
{
	char *tokn = strtok(prmpt, "\t\n");
	int v = 0;
	
	while (tokn != NULL && v < MAXIMUM_COMMAND - 1)
	{
		command[v] = strdup(tokn);
		if (command[v] == NULL)
		{
			perror("Memory allocation error");
			exit(1);
		}
		tokn = strtok(NULL, "\t\n");
		v++;
	}

void exec_prmpt(char **command)
{
pid_t child_processid = fork();
	if (child_processid < 0)
	{
		perror("Fork Failed");
		exit(1);
	}
	else if (child_processid == 0)
	{
		char *cmd_exec = command[0]; // Command to execute
		char full_path[MAX_DISPLAY_LENGTH] = "/bin/";
		myown_strcat(full_path, cmd_exec);
		
		if (execve(full_path, command, NULL) < 0)
		{
			perror("Exec error");
			exit(1);
		}
	}
	else
	{
		int report;
		waitpid(child_processid, &report, 0);
	}
}
