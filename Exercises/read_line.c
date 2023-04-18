#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#define CHUNK_SIZE 1024

/**
 * reallocate_buffer - reallocates a buffer
 * @lineptr: pointer to the buffer
 * @n: pointer to the size of the buffer
 *
 * Return: 0 on success, -1 on error
 */
int reallocate_buffer(char **lineptr, size_t *n)
{
	size_t new_size;
	char *new_ptr;

	new_size = *n + CHUNK_SIZE;
	new_ptr = realloc(*lineptr, new_size);
	if (new_ptr == NULL)
		return (-1);
	*lineptr = new_ptr;
	*n = new_size;

	return (0);
}

/**
 * _getline - reads an entire line from a stream
 * @lineptr: pointer to the buffer to hold the line
 * @n: pointer to the size of the buffer
 * @stream: stream to read from
 *
 * Return: number of characters read, -1 on error or end of file
 */
ssize_t _getline(char **lineptr, size_t *n, FILE *stream)
{
	int c;
	size_t pos;

	/* check for invalid arguments */
	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);

	/* allocate initial buffer if necessary */
	if (*lineptr == NULL)
	{
		*n = CHUNK_SIZE;
		*lineptr = malloc(CHUNK_SIZE);
		if (*lineptr == NULL)
			return (-1);
	}

	/* read characters from the stream */
	for (pos = 0; (c = fgetc(stream)) != EOF; pos++)
	{
		/* reallocate buffer if necessary */
		if (pos + 1 >= *n)
		{
			if (reallocate_buffer(lineptr, n) == -1)
				return (-1);
		}

		(*lineptr)[pos] = c;
		if (c == '\n')
			break;
	}

	/* check for end of file */
	if (pos == 0)
		return (-1);

	(*lineptr)[pos] = '\0';
	return (pos);
}

/**
 * main - reads lines from standard input and prints them
 *
 * Return: 0 on success
 */
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
