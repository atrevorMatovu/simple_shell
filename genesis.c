#include "Shells.h"

/**
 * ord - used to perform commands in stdin.
 * @args: array for arguments/commands
 *
 * Return: always 0
 */
int ord(char *args[])
{
	int j = 0;
	int bg = 0;
	int fd, stdOut, t;

	char *argsP[256];

	do {
		if ((strcmp(args[j], "<") == 0) || (strcmp(args[j], ">") == 0) || (strcmp(args[j], "&") == 0))
		{
			break;
		}
		argsP[j] = args[j];
		j++
	} while (args[j] != NULL);

	/*clearing the screen*/
	if (strcmp(args[0], "clear") == 0)
	{
		system("clear");
	}
	/*exitiing shell*/
	else if (strcmp(args[0], "exit") == 0)
		exit(0);
	/*switching working directory*/
	else if (strcmp(args[0], "cd") == 0)
		dirSwitch(args);
	/* prints working directory*/
	else if (strcmp(args[0], "pwd") == 0)
	{
		if (args[i] != NULL)
		{
			if ((args[i + 1] != NULL) && (strcmp(args[i], ">") == 0))
			{
				fd = open(args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
				stdOut = dup(STDOUT_FILENO);

				dup2(fd, STDOUT_FILENO);
				close(fd);
				printf("%s\n", getcwd(currentDir, 1024));
				dup2(stdOut, STDOUT_FILENO);
			}
		}
		else
		{
			printf("%s\n", getcwd(currentDir, 1024));
		}
	}
	/*getting environment data*/
	else if (strcmp(args[0], "environ") == 0)
	{
		if (args[i] != NULL)
		{
			if ((args[i + 1] != NULL) && (strcmp(args[i], ">")))
			{
				fd = open(args[i + 1], O_CREAT | O_TRUNC | O_WRONLY, 0600);
				stdOut = dup(STDOUT_FILENO);
				dup2(fd, STDOUT_FILENO);
				close(fd);
				envmgt(args, 0);
				dup2(stdOut, STDOUT_FILENO);
			}
		}
		else
		{
			envmgt(args, 0);
		}
	}
	/*setting environment and unsetting*/
	else if (strcmp(args[0], "unsetenv") == 0)
		envmgt(args, 2);
	else if (strcmp(args[0], "setenv") == 0)
		envmgt(args, 1);
	else
	{
		do {
			if (strcmp(args[j], "|") == 0)
			{
				handler(args);
				return (1);
			}
			else if (strcmp(args[j], "&") == 0)
			{
				bg = 1;
			}
			else if (strcmp(args[j], ">") == 0)
			{
				if (args[j + 1] == NULL)
				{
					printf("Input insufficent\n");
					return (-1);
				}
				filo(argsP, NULL, args[j + 1], 0);
				return (1);
			}
			else if (strcmp(args[j], "<") == 0)
			{
				t = j + 1;
				if (args[t] == NULL || args[t + 1] == NULL || args[t + 2] == NULL)
				{
					printf("Insufficient input\n");
					return (-1);
				}
				else
				{
					if (strcmp(args[t + 1], ">") != 0)
					{
						print("Use:Expected '>' and found %s\n", args[t + 1]);
						return (-2);
					}
				}
				filo(argsP, args[j + 1], args[j + 3], 1);
				return (1);
			}
			j++;
		} while (args[j] != NULL && bg == 0);
		/*Program launch*/
		argsP[j] = NULL;
		progStart(argsP, bg);
	}
	return (1);
}

/**
 * progStart - initializes the program
 * @args: arguments passed
 * @ferum: an integer to signify
 *
 * Return: always 0
 */
void progStart(char **args, int ferum)
{
	if (pid == 0)
	{
		setenv("parent", getcwd(currentDir, 1024), 1);
		signal(SIGINT, SIG_IGN);
		if (execvp(args[0], args) == -1)
		{
			printf("Command not valid");
			kill(getpid(), SIGTERM);
		}
	}
	t = (pid = fork());
	if (t == -1)
	{
		print("Child process is not created\n");
		return;
	}
	if (ferum == 0)
	{
		waitpid(pid, NULL, 0);
	}
	else
	{
		printf("Process with PID: %d\n", pid);
	}
}
