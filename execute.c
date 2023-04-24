#include "main.h"

void execute(char **argv)
{
	char *command = NULL;
	char *full_command = NULL;
	int status;
	pid_t child_pid;

	if (argv)
	{
		command = argv[0];
		full_command = get_path(command);

		child_pid = fork();
		if (child_pid == -1)
		{
			perror("Error");
			exit(1);
		}
		if (child_pid == 0)
		{
			/* execute the command in the child process */
			execve(full_command, argv, NULL);
			perror("Error");
			exit(1);
		}
		else
			/* wait for the child process to complete */
			wait(&status);
	}
}
