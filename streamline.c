#include "Shells.h"

/**
 * readstr - reads line from a stream
 *
 * Return: pointer.
 */
char *readstr(void)
{
	char *str = NULL;
	size_t c = 0;
	ssize_t getLine = getline(&str, &c, stdin);

	if (getLine == -1)
	{
		free(str);
		return (NULL);
	}
	return (str);
}

/**
 * divline - splits a line
 * @ln: ptr to character used
 *
 * Return: always 0
 */
char **divline(char *ln)
{
	const char *delim = " \t\r\n\a";
	const int max = 64;
	char **ens = malloc(max * sizeof(char));
	int count = 0;
	char *quart = strtok(ln, delim);

	do {
		ens[count] = quart;
		count++;

		if (count >= max)
		{
			break;
		}
		quart = strtok(NULL, delim);
	} while (quart != NULL);
	ens[count] = NULL;
	return (ens);
}
