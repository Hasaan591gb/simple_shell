#include "main.h"

/**
 * execute_command - executes a command
 * @full_command: full path of the command to be executed
 * @argv: array of arguments
 *
 * Description: The function creates a child process using the fork function.
 * In the child process, the command is executed using the execve function. If
 * execve fails, an error message is printed and the child process returns.
 *
 * In the parent process, the function waits for the child process to complete
 * using the wait function. If the child process did not exit normally, an
 * error message is printed and the function returns.
 */
void execute_command(char *full_command, char **argv)
{
	int status;
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("fork");
		return;
	}
	if (child_pid == 0)
	{
		/* execute the command in the child process */
		execve(full_command, argv, NULL);
		perror("execve");
		return;
	}
	else
	{
		/* wait for the child process to complete */
		if (wait(&status) == -1)
		{
			perror("wait");
			return;
		}
		if (!WIFEXITED(status))
		{
			fprintf(stderr, "%s: command failed\n", argv[0]);
			return;
		}
	}
}

/**
 * execute - finds and executes a command
 * @argv: array of arguments
 *
 * Description: The function takes an array of strings argv as an argument.
 * The first element of argv is the command to be executed. The function uses
 * the get_path function to find the full path of the command. If the command
 * is not found, an error message is printed and the function returns.
 *
 * The function then calls the execute_command function to create a child
 * process and execute the command.
 */
void execute(char **argv)
{
	char *command = NULL;
	char *full_command = NULL;

	if (argv)
	{
		command = argv[0];
		full_command = get_path(command);
		if (full_command == NULL)
		{
			fprintf(stderr, "%s: 1: %s not found\n", argv[0], command);
			return;
		}

		execute_command(full_command, argv);

		free(full_command);
	}
}
