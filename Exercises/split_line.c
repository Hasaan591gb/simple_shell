#include <stdio.h>
#include <string.h>

#define MAX_WORDS 100

char **split_string(char *str)
{
	char *array[MAX_WORDS];
	char *token;
	int i;

	token = strtok(str, " ");
	for (i = 0; token != NULL && i < MAX_WORDS; i++)
	{
		array[i] = token;
		token = strtok(NULL, " ");
	}

	return (array);
}
