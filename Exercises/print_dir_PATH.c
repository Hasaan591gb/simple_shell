#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * print_path - prints the directories in the system PATH
 */
void print_path(void)
{
	char *dir, *path, *path_copy;

	/* get the system PATH */
	path = getenv("PATH");
	if (path == NULL)
	{
		printf("PATH environment variable not found!\n");
		return;
	}

	/* make a copy of the PATH to avoid modifying the original */
	path_copy = strdup(path);

	/* split the PATH into directories and print each one */
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
}
