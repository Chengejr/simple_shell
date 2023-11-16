#include "shell.h"

/**
 * execute_command - Execute the given command using execve.
 *
 * @command: The command to execute.
 */
void execute_command(char *command)
{
	char *args[2];
	pid_t pid;
	int status;

	/* Remove the newline character at the end of the command */
	command[strcspn(command, "\n")] = 0;

	/* Set up the arguments for execve */
	args[0] = command;
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
		if (execve(command, args, NULL) == -1)
		{
			perror(command);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		/* Parent process */
		waitpid(pid, &status, 0);
	}
}

/**
 * main - Main function allowing the user to enter commands for execution.
 *
 * This function provides a basic shell interface where the user
 * can enter commands. The shell will execute the entered commands
 * and display the output, if any. It supports simple commands and
 * does not include advanced features such as piping, redirection, etc.
 *
 * Return: Always 0.
 */
int main(void)
{
	char *command = NULL;
	size_t bufsize = 0;

	while (1)
	{
		write(STDOUT_FILENO, "($)", 3);
		if (getline(&command, &bufsize, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(command);
			break;
		}

		execute_command(command);
	}

	free(command);
	return (0);
}

