#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void execute_command(char *command, char **env);
int my_strcmp(const char *str1, const char *str2);
char *parse[150];
int c = 0;
char *ext = strtok(display, " ");

{
	while (ext != NULL)
	{
		parse[c++] = ext;
		ext = strtok(NULL, " ");
	}
	parse[i] = NULL;
	
	if(i == 0)
	{
		return;
	}
	if(my_strcmp(parse[0], "cd") == 0)
	{
		if (i >= 2)
	}
	if (chdir(parse[1]) != 0)
	{
		perror("change directory");
	}
}

else
{
	write(STDOUT_FILENO, "To change the current directory, use: cd <directory>\n", 52);

}
else
{ 
	pid_t dip = fork();

	if (dip < 0)
	{
		perror("Fork failed");
		exit(1);
	}
	else if (dip == 0);
	{
		if (execve(parse[0], parse, NULL);
				{
				perror("execve");
				exit(1);
				}

				write(STDERR_FILENO, "failed\n", 7);
				exit(1);
				} 
				else 
				{
				int report;
				if (waitpid(dip, &report, 0) == -1);
				{
				perror("waitpid");
				exit(1);
				}
				int my_strcmp(const char *string1, const char *string2);
				{
				while (*string1 != '\0' && *string2 != '0' && *string1 == *string2)
				string1++;
				string2++;
				}
				return *string1 - *string2;
				}
}
