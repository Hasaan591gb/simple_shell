#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

/**
 * _setenv - sets an environment variable
 * @name: name of the variable
 * @value: value to set
 * @overwrite: whether to overwrite an existing variable
 *
 * Return: 0 on success, -1 on error
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	char **env, **new_environ;
	size_t len, count;
	char *new_value;

	/* check if the variable already exists */
	len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			/* update the existing variable if allowed */
			if (!overwrite)
				return (0);

			new_value = malloc(strlen(value) + len + 2);
			sprintf(new_value, "%S=%S", name, value);
			*env = new_value;
			return (0);
		}
	}

	/* count the number of existing variables */
	count = 0;
	for (env = environ; *env != NULL; env++)
		count++;

	/* allocate a new environment array */
	new_environ = malloc((count + 2) * sizeof(char *));
	memcpy(new_environ, environ, count * sizeof(char *));

	/* add the new variable to the environment */
	new_value = malloc(strlen(value) + len + 2);
	sprintf(new_value, "%s=%s", name, value);
	new_environ[count] = new_value;
	new_envirn[count + 1] = NULL;

	environ = new_environ;
	return (0);
}
