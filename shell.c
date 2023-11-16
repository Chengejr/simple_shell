#include "shell.h"

/**
 * executeCommand - Execute the given command using execve.
 *
 * @command: The command to execute.
 */
void executeCommand(char *command)
{
	char *args[2];
	char *token;
	pid_t pid;
	int status;

	/* Remove the newline character at the end of the command */
	command[strcspn(command, "\n")] = 0;

	/* Set up the arguments for execve */
	token = strtok(command, " ");
	args[0] = token;
	args[1] = NULL;

	/* Fork a child process */
	pid = fork();

	if (pid < 0)
	{
		perror("fork");
	}
	else if (pid == 0)
	{
		/* Child process */
		if (execve(args[0], args, NULL) == -1)
		{
			perror(args[0]);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}

