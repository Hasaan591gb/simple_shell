#include <stdio.h>
/* #include "main.h" */

char *_f_strchr(const char *str, int character);

/**
 * _f_strtok - choves one token at a time using delimiter until NULL.
 * @str: string to be tokenised
 * @delimiter: termination point
 * Return: string/token
 */

char *_f_strtok(char *str, const char *delimiter)
{
	char *token = NULL;
	static char *previous_token;

	/* Checking for the end of the string */
	if (str == NULL && previous_token == NULL)
		return (NULL);

	/* initialising the previous token to the start of the string */
	if (str != NULL)
	{
		previous_token = str;
	}

	token = previous_token;

	/* Iterating through searching for the next delimiter or NULL*/
	while (*previous_token != '\0')
	{
		const char *delimiter_position = _f_strchr(delimiter, *previous_token);

		if (delimiter_position != NULL)
		{
			/* Replacing the delimiter with a null character */
			*previous_token++ = '\0';
			break;
		}
		++previous_token;
	}

	/* In case no new tokens were found */
	if (previous_token == token || (*token == '\0' && *previous_token == '\0'))
	{
		previous_token = NULL;
		return (NULL);
	}

	return (token);
}

/**
 * _f_strchr - find occurence of the given string
 * @str: string to be searched
 * @character: character to be searched for.
 * Return: position
 */
char *_f_strchr(const char *str, int character)
{
	/* Incase null character is passed*/
	if (!character)
		return ((char *)str);

	/* Iterating through the string until character is found*/
	while (*str)
	{
		if (*str == character)
			return ((char *)str);
		++str;
	}

	/* Incase the character isn't found at all */
	return (NULL);
}
