#include "main.h"

/**
 * _strtok - choves one token at a time using delimiter until NULL.
 * @str: string to be tokenised
 * @delim: termination point
 *
 * Description: This function is an implementation of the strtok function
 *		that does not use any external functions. It takes in a string and a
 *		delimiter and returns one token at a time until it reaches the end of
 *		the string. Consecutive delimiters are treated as a single delimiter
 *		and empty tokens are not returned.
 *
 * Return: string/token
 */
char *_strtok(char *str, const char *delim)
{
	/* Static variable to keep track of where the previous token ended */
	static char *next_token;

	/* Pointer to the start of the current token */
	char *current_token;

	const char *delim_char;

	if (str)
		next_token = str;

	/* Skip any leading delimiters */
	while (*next_token)
	{
		for (delim_char = delim; *delim_char; ++delim_char)
			if (*next_token == *delim_char)
				break;
		if (!*delim_char)
			break;
		++next_token;
	}
	if (!*next_token)
		return (NULL);

	current_token = next_token;

	/* Search for the next delimiter or the end of the string */
	while (*next_token)
	{
		for (delim_char = delim; *delim_char; ++delim_char)
			if (*next_token == *delim_char)
				break;
		if (*delim_char)
			break;
		++next_token;
	}
	if (*next_token)
		*next_token++ = '\0';

	return (current_token);
}
