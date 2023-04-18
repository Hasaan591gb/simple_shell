#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_WORDS 10

/**
 * split_string - splits a string into an array of words
 * @str: the string to split
 *
 * Return: array of words
 */
char **split_string(char *str)
{
	char **array;
	char *token;
	size_t size, count;

	/* allocate initial memory for the array */
	size = CHUNK_SIZE;
	array = malloc(size * sizeof(char *));
	if (array == NULL)
		return (NULL);

	/* split the string into words */
	count = 0;
	token = strtok(str, " ");
	while (token != NULL)
	{
		/* reallocate memory for the array if necessary */
		if (count >= size)
		{
			size += CHUNK_SIZE;
			array = realloc(array, size * sizeof(char *));
			if (array == NULL)
				return (NULL);
		}

		array[count++] = token;
		token = strtok(NULL, " ");
	}

	/* add a NULL terminator to the array */
	array[count] = NULL;

	return (array);
}
