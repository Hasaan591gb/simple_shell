#include <stdio.h>
#include <string.h>

extern char **environ;

/**
 * _getenv - gets the value of an environment variable
 * @name: name of the variable
 *
 * Return: value of the variable, or NULL if not found
 */
char *_getenv(const char *name)
{
	size_t len;
	char **env;

	/* check if the variable exists */
	len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
	}

	/* variable not found */
	return (NULL);
}
