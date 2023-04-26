#include "main.h"

/**
 * _getline - reads a line from standard input
 *
 * @lineptr: pointer to the buffer to store the line
 * @n: size of the buffer
 *
 * Return: number of characters read, or -1 on error or end of file
 */
ssize_t _getline(char **lineptr, size_t *n)
{
	static char buffer[BUFFER_SIZE];
	static size_t start, end;
	size_t len = 0;
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
			if (nread <= 0)
				return (nread);
			start = 0, end = nread;
		}
		while (start < end)
		{
			if (len >= *n - 1)
			{
				*n *= 2;
				*lineptr = realloc(*lineptr, *n);
				if (*lineptr == NULL)
					return (-1);
			}
			(*lineptr)[len++] = buffer[start++];
			if ((*lineptr)[len - 1] == '\n')
			{
				(*lineptr)[len] = '\0';
				return (len);
			}
		}
	}
	return (-1);
}
