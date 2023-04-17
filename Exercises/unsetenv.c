#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern char **environ;

int _unsetenv(const char *name)
{
	char **env, **ptr;
	size_t len;

	if (name == NULL || *name == '\0' || strchr(name, '=') != NULL)
		return (-1);

	len = strlen(name);
	for (env = environ; *env != NULL;)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
		{
			ptr = env;
			free(*env);
			do
				*ptr = *(ptr + 1);
			while (*ptr++);
		}
		else
			env++;
	}

	return (0);
}
