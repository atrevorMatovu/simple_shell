#include "Shells.h"

/**
 * begin - function to start our shell
 *
 * Return: 0 always
 */
void begin(void)
{
	shellPID = getpid();

	SH_INTERACTIVE = isatty(STDIN_FILENO);

	if (SH_INTERACTIVE)
	{
		do {
			kill(shellPID, SIGTTIN);
		} while (tcgetpgrp(STDIN_FILENO) != (shellPGID = getpgrp()));
		
		childAction.sa_handler = sig_child;
		intAction.sa_handler = sig_int;

		sigaction(SIGCHLD, &childAction, 0);
		sigaction(SIGINT, &intAction, 0);
		setpgid(shellPID, shellPID);
		shellPGID = getpgrp();

		if (shellPID != shellPGID)
		{
			printf("Error: The shell is not the process group leader");
			exit(EXIT_FAILURE);
		}
		tcsetpgrp(STDIN_FILENO, shellPGID);
		tcgetattr(STDIN_FILENO, &shellAttributes);
		currentDir = (char *) calloc(1024, sizeof(char));
	}
	else
	{
		printf("Could not make the shell interactive.\n");
		exit(EXIT_FAILURE);
	}
}

/**
 * uninteractive - kinda like offline mode
 *
 * Return: nothing.
 */
void uninteractive(void)
{
	char **tr, *hn;
	int lash = -1;

	while (1)
	{
		hn = readstr();
		if (hn == NULL)
		{
			break;
		}
		tr = divline(hn);
		lash = execar(tr);
		free(hn);
		free(tr);
		if (lash == 0)
		{
			break;
		}
	}
}

/**
 * execar - to execute commands
 * @args: pointer
 *
 * Return: always 0
 */
int execar(char **args)
{
	if (args[0] != NULL && strcmp(args[0], "exit") == 0)
	{
		return (0);
	}
	else
	{
		return (-1);
	}
}
