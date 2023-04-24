#include "main.h"

char *get_path(char *command)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	char full_path[1024];
	struct stat buffer;

	while (dir != NULL)
	{
		snprintf(full_path, 1024, "%s/%s", dir, command);
		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	if (stat(command, &buffer) == 0)
		return (strdup(command));

	free(path_copy);
	return (NULL);
}
