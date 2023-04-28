#include "main.h"

/**
 * read_line - reads a line from a buffer
 * @buffer: buffer to read from
 * @start: start index in the buffer
 * @end: end index in the buffer
 * @lineptr: pointer to the buffer to store the line
 * @n: size of the buffer
 *
 * Return: number of characters read, or -1 on error
 *
 * Description: The function reads characters from the buffer and stores them
 * in the buffer pointed to by lineptr. If the buffer pointed to by lineptr is
 * not large enough to store the entire line, it is reallocated to be twice its
 * current size. The function returns the number of characters read or -1 on
 * error.
 */
ssize_t read_line(char *buffer, size_t *start,
		size_t end, char **lineptr, size_t *n)
{
	size_t len = 0;

	while (*start < end)
	{
		if (len >= *n - 1)
		{
			*n *= 2;
			*lineptr = realloc(*lineptr, *n);
			if (*lineptr == NULL)
				return (-1);
		}

		(*lineptr)[len++] = buffer[(*start)++];
		if ((*lineptr)[len - 1] == '\n')
		{
			(*lineptr)[len] = '\0';
			return (len);
		}
	}

	return (len);
}

/**
 * _getline - reads a line from standard input
 * @lineptr: pointer to the buffer to store the line
 * @n: size of the buffer
 *
 * Return: number of characters read, or -1 on error or end of file
 *
 * Description: The function reads a line from standard input and stores it in
 * a buffer pointed to by lineptr. The size of the buffer is stored in n. The
 * function uses a static buffer of size BUFFER_SIZE to read from standard
 * input using the read function. If the buffer pointed to by lineptr is not
 * large enough to store the entire line, it is reallocated to be twice its
 * current size. The function returns the number of characters read or -1 on
 * error or end of file.
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[BUFFER_SIZE];
	static size_t start, end;
	ssize_t nread;

	if (lineptr == NULL || n == NULL)
		return (-1);

	if (*lineptr == NULL)
	{
		*lineptr = malloc(BUFFER_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUFFER_SIZE;
	}

	while (1)
	{
		if (start >= end)
		{
			nread = read(STDIN_FILENO, buffer, BUFFER_SIZE);
			if (nread == 0)
			{
				printf("\n");
				exit(EXIT_SUCCESS);
			}
			if (nread < 0)
				return (nread);
			start = 0;
			end = nread;
		}

		nread = read_line(buffer, &start, end, lineptr, n);
		if (nread > 0 && (*lineptr)[nread - 1] == '\n')
			return (nread);
	}

	return (-1);
}
