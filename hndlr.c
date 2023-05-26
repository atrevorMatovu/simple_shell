#include "Shells.h"

/**
 * sig_child - handler for a child process
 * @t: integer used
 *
 * Return: always 0
 */
void sig_child(int t)
{
	int stat;

	pid_t childPid;

	while ((childPid = waitpid(-1, &stat, WNOHANG)) > 0)
	{
		/*process the terminated child process*/
	}
	printf("\n");
}

/**
 * sig_int - handler for sending signal to child process
 * and response.
 * @t: integer parsed to.
 *
 * Return: always 0
 */
void sig_int(int t)
{
	if (kill(pid, SIGTERM) == 0)
	{
		printf("\n SIGINT signal sent to process %d\n", pid);
		noPrompt = 1;
	}
	else
	{
		printf("\n");
	}
}

/**
 * tunnels - used to handle channels
 * @args: array of arguments.
 *
 * Return: always 0
 */
void tunnels(char *args[])
{
	int Cmd = 0;
	int fd[2];
	int fds[2];
	pid_t pid;
	int t = 0;
	int i = 0;
	int j = 0;
	int num = 0;
	int num2 = 0;
	char *ord[256];

	while (args[num] != NULL)
	{
		if (strcmp(args[num], "|") == 0)
		{
			Cmd++;
		}
		num++;
	}
	Cmd++;
	while (args[i] != NULL && t != 1)
	{
		while (strcmp(args[i], "|") != 0)
		{
			ord[num2] = args[i];
			i++;

			if (args[i] == NULL)
			{
				t = 1;
				num2++;
				break;
			}
			num2++;
		}
		ord[num2] = NULL;
		i++;

		if (j % 2 != 0)
		{
			pipe(fd);
		}
		else
		{
			pipe(fds);
		}

		pid = fork();

		if (pid == -1)
		{
			if (j != (Cmd - 1))
			{
				if ((j % 2) != 0)
				{
					close(fd[1]);
				}
				else
				{
					close(fds[1]);
				}
				printf("Child process can not be created\n");
				return;
			}
			if (pid == 0)
			{
				if (j == 0)
				{
					dup2(fds[1], STDOUT_FILENO);
				}
				else if (j == (Cmd - 1))
				{
					if ((Cmd % 2) != 0)
					{
						dup2(fd[0], STDIN_FILENO);
					}
					else
					{
						dup2(fds[0], STDIN_FILENO);
					}
				}
				else
				{
					if ((j % 2) != 0)
					{
						dup2(fds[0], STDIN_FILENO);
						dup2(fd[1], STDOUT_FILENO);
					}
					else
					{
						dup2(fd[0], STDIN_FILENO);
						dup2(fds[1], STDOUT_FILENO);
					}
				}
				if (execvp(ord[0], ord) == -1)
				{
					kill(getpid(), SIGTERM);
				}
			}
			if (j == 0)
			{
				close(fds[1]);
			}
			else if (j == (Cmd - 1))
			{
				if ((Cmd % 2) != 0)
				{
					close(fd[0]);
				}
				else
				{
					close(fds[0]);
				}
			}
			else
			{
				if ((j % 2) != 0)
				{
					close(fds[0]);
					close(fd[1]);
				}
				else
				{
					close(fd[0]);
					close(fds[1]);
				}
			}
			waitpid(pid, NULL, 0);
			j++;
		}
	}
}
