#include <stdio.h>
#include <string.h>	  /* strlen*/
#include <stdlib.h>	  /* Malloc */
#include <unistd.h>	  /* execve */
#include <sys/wait.h> /* wait */

/* Prototypes */
char *reader(char *buffer, size_t len);
char **tokenisor(char *cmd_tokens[], char *buffer, char *delimiter, int index);
int executor(char **argv, int error);

/**
 * main - Shell Entry Point
 * Return: 0 for success
 */

int main(void)
{
	/* Declarations */
	size_t len;
	char *buffer;
	char *delimiter;
	char **cmd_tokens;
	int index, error;

	/* Initialiations */
	len = 20;
	delimiter = " ";
	cmd_tokens = NULL;
	index = error = 0;

	/**
	 * STARTING THE SHELL
	 * Infinite loop - to be adjusted to terminate when user inputs exit.
	 */

	while (1)
	{
		/* READ COMMANDS into the buffer */
		buffer = reader(buffer, len);

		/* TOKENISE buffer into an array of tokens */
		cmd_tokens = tokenisor(cmd_tokens, buffer, delimiter, index);

		/* EXECUTE tokens via shell */
		executor(cmd_tokens, error);
	}
	return (0);
}

/**
 * reader - reads input from the user to the buffer
 * @buffer: to store input string
 * @len: initial length for buffer malloc, getline will adjest it if need arise
 * Return: buffer with read string
 */
char *reader(char *buffer, size_t len)
{
	/* Allocating memory for the buffer to store input */
	buffer = malloc(sizeof(char) * len);

	/* Checking if memory was created */
	if (buffer == NULL)
	{
		printf("Error: Couldn't allocate memory");
		return (0);
	}

	/* Shell username Group name: Viestar -  Hasaan */
	printf("\nviesaan $ ");

	/**
	 * READING.
	 * Getline will use realloc to assign more bytes to the buffer if needed.
	 * buffer - Full String with all the commands separated by a delimeter
	 */
	getline(&buffer, &len, stdin);
	printf("Reading your command now, hold on please ...");
	printf(" ... ...\n");
	printf("\nUser commandline string: %s\n", buffer);

	/* Returning a string from user for tokenising */
	return (buffer);
}

/**
 * tokenisor - creates an array of tokens from the commandline string
 * @cmd_tokens: empty array to store tokens
 * @buffer: string of commands input by the user
 * @delimiter: user commands' separator.
 * @index: used in appending the tokens array.
 * Return: Pointer to the array of tokens.
 */

char **tokenisor(char *cmd_tokens[], char *buffer, char *delimiter, int index)
{
	int count;
	/**
	 * TOKENISING
	 * strtok - splits buffer into cmd_tokens using any specified delimeter.
	 */
	sleep(1);
	printf("Now tokenising ... .wait a few seconds.");
	printf(" ... ...\n");

	/* Allocating memory for the array of tokens */
	cmd_tokens = malloc(strlen(buffer));

	/* Checking if memory was created */
	if (cmd_tokens == NULL)
	{
		printf("Error: Couldn't allocate memory");
		return (0);
	}

	/* Fetching the first token */
	cmd_tokens[index] = strtok(buffer, delimiter);

	/* Loop to collect more than one token using strtok function */
	while (cmd_tokens[index])
	{
		++index;
		cmd_tokens[index] = strtok(NULL, delimiter);
	}

	/* Loop to display tokens individually */
	for (count = 0; count <= index; count++)
	{
		printf("Token[%d] --> %s\n", count, cmd_tokens[count]);
	}
	return (cmd_tokens);
}

/**
 * executor - Executes tokens passed in an array
 * @argv: Array of tokens
 * @error: variable to save a return value of execve
 * Return: 0 for success and -1 if failed.
 */

int executor(char **argv, int error)
{
	/* Process ignition */
	sleep(2);
	printf("\nNow executing using execve ...");
	printf(" ... ...\n");

	/* The execve function to execute commands respectively and exit after */
	error = execve(argv[0], argv, NULL);

	/* Execve returns -1 in case of an error */
	if (error == -1)
	{
		perror("Error: ");
	}
	printf("Done executing.\n");
	return (0);
}
