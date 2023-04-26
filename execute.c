#include "main.h"
/**
 * execute - Executors
 * @argv: array of arguments
 */
void execute(char **argv)
{
	char *command = NULL, *full_command = NULL;
	int status;
	pid_t child_pid;

	if (argv)
	{
		command = argv[0];
		full_command = get_path(command);
		if (full_command == NULL)
		{
			fprintf(stderr, "%s: 1: %s not found\n", argv[0], command);
			exit(EXIT_FAILURE);
		}
		child_pid = fork();
		if (child_pid == -1)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		if (child_pid == 0)
		{
			execve(full_command, argv, NULL); /* execute the child process */
			perror("execve");
			exit(EXIT_FAILURE);
		}
		else
		{
			if (wait(&status) == -1) /* wait 4 the child process to complete */
			{
				perror("wait");
				exit(EXIT_FAILURE);
			}
			if (!WIFEXITED(status))
			{
				fprintf(stderr, "%s: command failed\n", command);
				exit(EXIT_FAILURE);
			}
		}
		free(full_command);
	}
}
