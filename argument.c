#include "shell.h"

/**
 * handle_arguments - Simple shell implementation that allows
 * the user to enter commands for execution.
 *
 * This function provides a basic shell interface where the user
 * can enter commands. The shell will execute the entered commands
 * and display the output, if any. It supports simple commands and
 * arguments.
 */
void handle_arguments(void)
{
	char *command = NULL;
	size_t bufsize = 0;
	char *args[64];
	pid_t pid;
	int status;

	while (1)
	{
		write(STDOUT_FILENO, "$: ", 3);
		if (getline(&command, &bufsize, stdin) == -1)
		{
			write(STDOUT_FILENO, "\n", 1);
			if (command != NULL)
			{
				free(command);
				command = NULL;
			}
			break;
		}

		command[strcspn(command, "\n")] = '\0';
		parse_command(command, args);
		pid = fork();

		if (pid < 0)
		{
			perror("fork");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			/* Child process */
			execute_command(args);
		}
		else
		{
			/* Parent process */
			waitpid(pid, &status, 0);
		}
		if (command != NULL)
		{
		free(command);
		command = NULL;
		}
	}
}

/**
 * parse_command - Parse command function to split a command
 * and store the arguments in an array
 * @command: The command to be parsed
 * @args: An array to store the parsed arguments
 */
void parse_command(const char *command, char *args[])
{
	char *token;
	int arg_count = 0;

	token = strtok((char *)command, " ");
	while (token != NULL && arg_count < 63)
	{
		args[arg_count] = token;
		arg_count++;
		token = strtok(NULL, " ");
	}
	args[arg_count] = NULL;
}

/**
 * execute_command - Execute command with the provided arguments
 * using execvp
 * This function takes an array of arguments
 * @args: An array of arguments representing the command to execute
 */
void execute_command(char *args[])
{
	if (execvp(args[0], args) == -1)
	{
		perror(args[0]);
		exit(EXIT_FAILURE);
	}
}
