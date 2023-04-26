#include "main.h"

/**
 * get_path - finds the full path of a command
 * @command: command to find the full path of
 *
 * Return: full path of the command, or NULL if not found
 *
 * Description: The function takes a command string as an argument and returns
 * the full path of the command by searching the directories listed in the PATH
 * environment variable. The function uses the getenv function to get the value
 * of the PATH environment variable and then tokenizes it using the strtok
 * function with ":" as a delimiter. For each directory in PATH, the function
 * constructs the full path of the command by appending it to the directory and
 * checks if the file exists and is executable using the stat and access
 * functions. If the file is found and is executable, its full path is
 * returned. If the file is not found in any of the directories in PATH, the
 * function checks if it exists and is executable in the current directory. If
 * it is, its path is returned. Otherwise, the function returns NULL.
 */
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
		if (stat(full_path, &buffer) == 0 && access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (strdup(full_path));
		}
		dir = strtok(NULL, ":");
	}

	if (stat(command, &buffer) == 0 && access(command, X_OK) == 0)
		return (strdup(command));

	free(path_copy);
	return (NULL);
}
