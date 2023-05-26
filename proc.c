#include "Shells.h"

/**
 * readln - reads astring
 *
 * Return: void
 */
char *readln(void)
{
	int p = 0;
	char *sh = malloc(sizeof(char) * 1024);
	int i;
	int t;

	if (!sh)
	{
		fprintf(stderr, "Found error\n");
		exit(EXIT_FAILURE);
	}
	do {
		i = getchar();

		if (i == EOF || i == '\n')
		{
			sh[p] = '\0';
			return (sh);
		}
		else
		{
			sh[p] = i;
		}
		p++;

		if (p >= 1024)
		{
			t = (2 * 1024);
			sh = realloc(sh, t);
			if (!sh)
			{
				fprintf(stderr, "Found error\n");
				exit(EXIT_FAILURE);
			}
		}
	}
}

/**
 * newProc - creates new process
 * @tp: array of strings that contain commands
 *
 * Return: 1 success, 0 otherwise.
 */
int newProc(char **tp)
{
	pid_t pid;
	int sys;

	pid = fork();
	if (pid ==  0)
	{
		if (execar(tp[0], tp) == -1)
		{
			perror("Error found in new process");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("Error forking in new process");
	}
	else
	{
		do {
			waitpid(pid, &sys, WUNTRACED);
		} while (!WIFEXITED(sys) && !WIFSIGNALED(sys));
	}
	return (-1);
}
