#include "shell.h"

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
		write(STDOUT_FILENO, "#cisfun$ ", 9);
		if (getline(&command, &bufsize, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(command);
			break;
		}

		executeCommand(command);
	}

	free(command);
	return (0);
}

