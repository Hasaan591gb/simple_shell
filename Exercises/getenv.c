#include <stdio.h>
#include <string.h>

extern char **environ;

char *_getenv(const char *name)
{
	size_t len;
	char **env;

	len = strlen(name);
	for (env = environ; *env != NULL; env++)
	{
		if (strncmp(*env, name, len) == 0 && (*env)[len] == '=')
			return (*env + len + 1);
	}

	return (NULL);
}
