#include "Shells.h"

/**
 * envmgt - manages the environment properties
 * @args: array of arguments passed
 * @alt: option
 *
 * Return: always 0
 */
int envmgt(char *args[], int alt)
{
	char **t;

	if (alt == 0)
	{
		for (t = environ; *t != 0; t++)
		{
			printf("%s\n", *t);
		}
	}
	else if (option == 1)
	{
		if (args[1] == NULL || args[2] == NULL)
		{
			printf("%s", "Insufficient arguments\n");
			return (-1);
		}
		if (getenv(args[1]) != NULL)
		{
			printf("%s", "The variable is overwritten\n");
		}
		else
		{
			printf("%s", "The variable is created\n");
		}
		if (args[2] == NULL)
		{
			setenv(args[1], "", 1);
		}
		else
		{
			setenv(args[1], args[2], 1);
		}
	}
	else if (option == 2)
	{
		if (args[1] == NULL)
		{
			printf("%s", "Insufficent arguments\n");
			return (-1);
		}
		if (getenv(args[1]) != NULL)
		{
			unsetenv(args[1]);
			printf("%s", "The variable is erased\n");
		}
		else
		{
			printf("%s", "The variable not existing\n");
		}
	}
	else
	{
		printf("%s", "Invalid alternative\n");
	}
	return (0);
}

/**
 * filo - manage I/O
 * @inputFile: the input file argument
 * @outputFile: output file argument
 * @alt: option
 * @args: array of arguments passed
 *
 * Return: always 0
 */
void filo(char *args[], char *inputFile, char *outputFile, int alt)
{
	int fd;

	t = (pid = fork());
	if (t == -1)
	{
		printf("failed to create child process\n");
		return;
	}
	if (pid == 0)
	{
		switch (alt)
		{
			case 0:
				fd = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break;
			case 1:
				fd = open(inputFile, O_RDONLY, 0600);
				dup2(fd, STDIN_FILENO);
				close(fd);
				/*for the output as well*/
				fd = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600);
				dup2(fd, STDOUT_FILENO);
				close(fd);
				break;
		}
		setenv("parent", getcwd(currentDir, 1024), 1);
		if (execvp(args[0], args) == -1)
		{
			printf(-1);
			kill(getpid(), SIGTERM);
		}
	}
	waitpid(pid, NULL, 0);
}
