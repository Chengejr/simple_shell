#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

#define MAX_INPUT_SIZE 1024

/**
 * execute_command - Execute the given command in a child process
 * @command: The command to execute
 */
void execute_command(char *command)
{
	pid_t pid;
	int status;

	pid = fork();

	if (pid == 0)
	{
		/* Child process */
		char **args = malloc(2 * sizeof(char *));

		if (args == NULL)
		{
			perror("malloc");
			exit(EXIT_FAILURE);
		}

		args[0] = command;
		args[1] = NULL;

		execve(command, args, NULL);
		perror("execve");
		free(args);  /* Free allocated memory */
		_exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		/* Fork failed */
		perror("fork");
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}

/**
 * main - The main function for the simple shell
 * Return: Always 0
 */
int main(void)
{
	char input[MAX_INPUT_SIZE];

	while (1)
	{
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (fgets(input, sizeof(input), stdin) == NULL)
		{
			/* Handle end-of-file (Ctrl+D) */
			write(STDOUT_FILENO, "\n", 1);
			break;
		}

		/* Remove newline character */
		input[strcspn(input, "\n")] = '\0';

		if (strcmp(input, "exit") == 0)
		{
			break;
		}

		execute_command(input);
	}

	return (0);
}

