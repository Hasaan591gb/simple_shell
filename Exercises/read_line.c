#include <stdio.h>
#include <stdlib.h>

#define CHUNK_SIZE 1024

ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int c;
	size_t pos, new_size;
	char *new_ptr;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		*n = CHUNK_SIZE;
		*lineptr = malloc(CHUNK_SIZE);
		if (*lineptr == NULL)
			return (-1);
	}

	for (pos = 0; (c = fgetc(stream)) != EOF; pos++)
	{
		if (pos + 1 >= *n)
		{
			new_size = *n + CHUNK_SIZE;
			new_ptr = realloc(*lineptr, new_size);
			if (new_ptr == NULL)
				return (-1);
			*lineptr = new_ptr;
			*n = new_size;
		}

		(*lineptr)[pos] = c;
		if (c == '\n')
			break;
	}

	if (pos == 0)
		return (-1);

	(*lineptr)[pos] = '\0';
	return (pos);
}

int main(void)
{
	char *buffer = NULL;
	size_t len = 0;
	ssize_t read;

	printf("$ ");
	while ((read = _getline(&buffer, &len, stdin)) != -1)
		printf("%s\n$ ", buffer);

	free(buffer);
	return (0);
}
