#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _setenv(const char *name, const char *value, int overwrite)
{
	char **env, **new_environ;
	size_t len, count;
	char *new_value;

	len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			if (!overwrite)
				return (0);

			new_value = malloc(strlen(value) + len + 2);
			sprintf(new_value, "%S=%S", name, value);
			*env = new_value;
			return (0);
		}
	}

	count = 0;
	for (env = environ; *env != NULL; env++)
		count++;

	new_environ = malloc ((count + 2) * sizeof(char *));
	memcpy(new_environ, environ, count * sizeof(char *));

	new_value = malloc(strlen(value) + len + 2);
	sprintf(new_value, "%s=%s", name, value);
	new_environ[count] = new_value;
	new_envirn[count + 1] = NULL;

	environ = new_environ;
	return (0);
}
