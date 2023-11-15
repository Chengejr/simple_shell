#include "shell.h"

void printPrompt(void)
{
	write(STDOUT_FILENO, "$: ", 2);
}
char *readInput(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read;
	size_t input_length;

	if (read == -1)
	{
		write(STDOUT_FILENO, "\n", 1);
		free(input);
		exit(EXIT_SUCCESS);
	}
	input_length = strlen(input);
	if (input[input_length - 1] == '\n')
	{
		input[input_length - 1] = '\0';
	}
	return (input);
}
void printEnvironment(void)
{
	char **env = environ;
	size_t env_length;

	while (*env)
	{
		env_length = strlen(*env);
		write(STDOUT_FILENO, *env, env_length);
		write(STDOUT_FILENO, "\n", 1);
		env++;
	}
}
void executeCommand(char **args)
{
	pid_t pid = fork();

	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
		{
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}

