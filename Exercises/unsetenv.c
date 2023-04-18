#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _unsetenv - function that deletes the variable name from the environment
 * @name: name of the variable to be deleted
 *
 * Return: 0 on success, -1 on failure
 */
int _unsetenv(const char *name)
{
	char **env, **ptr;
	size_t len;

	/* Check if name is valid */
	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (-1);

	len = strlen(name);
	for (env = environ; *env != NULL;)
	{
		/* Check if variable matches name */
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			ptr = env;
			free(*env);
			/* Shift remaining variables up */
			do
				(*ptr) = *(ptr + 1);
			while (*ptr++);
		}
		else
			env++;
	}

	return (0);
}
