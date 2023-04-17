#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_path(void)
{
	char *dir, *path, *path_copy;

	path = getenv("PATH");
	if (path == NULL)
	{
		printf("PATH environment variable not found!\n");
		return;
	}

	path_copy = strdup(path);
	dir = strtok(path_copy, ":");
	while (dir != NULL)
	{
		printf("%s\n", dir);
		dir = strtok(NULL, ":");
	}

	free(path_copy);
}
