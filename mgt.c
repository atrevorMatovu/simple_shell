#include "Shells.h"

/**
 * dirSwitch - changes directory
 * @args: array of arguments
 *
 * Return: always 0
 */
int dirSwitch(char *args[])
{
	if (args[1] == NULL)
	{
		chdir(getenv("HOME"));
		return (1);
	}
	else
	{
		while (chdir(args[1]) == -1)
		{
			printf(" %s: not existing directory\n", args[1]);
			return (-1);
		}
	}
	return (0);
}

/**
 *shPpt - displays shell prompt
 *Return: always 0
 */
void shPpt(void)
{
	char lost[MAX_HOSTNAME_LEN];

	if (gethostname(lost, sizeof(lost)) != 0)
	{
		perror("gethostname");
		return;
	}

	char currentDir[MAX_CMD_LEN];

	if (getcwd(currentDir, sizeof(currentDir)) == NULL)
	{
		perror("getcwd");
		return;
	}
	printf("%s@%s %s > ", getlogin(), lost, currentDir);
}
