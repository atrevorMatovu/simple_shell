#include "Shells.h"

/**
 * begin - function to start our shell
 *
 * Return: 0 always
 */
void begin()
{
	pid_t shellPID = getpid();
	SH_INTERACTIVE = isatty(STDIB_FILENO);

	if (SH_INTERACTIVE)
	{
		do {
			kill(shellPID, SIGTTIN);
		} while(tcgetpgrp(STDIN_FILENO) != (shellPGID = getpgrp()));

		struct sigaction childAction;
		struct sigaction intAction;

		childAction.sa_handler = childSignalHandler;
		intAction.sa_handler = intSignalHandler;

		sigaction(SIGCHLD, &childAction, 0);
		sigaction(SIGINT, &intAction, 0);
		setpgid(shellPID, shellPID);setpgid(shellPID, shellPID);
		shellPGID = getpgrp();

		if (shellPID != shellPGID)
		{
			printf("Error: The shell is not the process group leader");
			exit(EXIT_FAILURE);
		}
		tcsetpgrp(STDIN_FILENO, shellPGID);
		tcgetattr(STDIN_FILENO, &shellAttributes);
		currentDirectory = (char*)calloc(1024, sizeof(char));
	}
	else
	{
		printf("Could not make the shell interactive.\n");
		exit(EXIT_FAILURE);
	}
}

/**
 *
