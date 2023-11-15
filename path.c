#include "shell.h"
/**
 * printPrompt - Displays the shell prompt.
 *
 * Description:
 *   This function writes the shell prompt "$: " to the standard output.
 *   It serves as an indicator for the user to enter commands.
 */
void printPrompt(void)
{
	write(STDOUT_FILENO, "$: ", 2);
}
/**
 * readInput - Reads a line of input from the user.
 *
 * Description:
 *   Reads a line of input using getline, removes the newline character,
 *   and returns the dynamically allocated string. Exits on end of file.
 *
 * Returns:
 *   A dynamically allocated string containing the user input.
 *   The caller is responsible for freeing the allocated memory.
 */
	char *readInput(void)
{
	char *input = NULL;
	size_t len = 0;
	ssize_t read = getline(&input, &len, stdin);
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

/**
 * printEnvironment - Prints the current environment variables.
 *
 * Description:
 *   This function prints each environment variable along with a newline.
 *
 * Usage:
 *   printEnvironment();
 */
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

/**
 * tokenizeInput - Tokenizes a string input based on spaces
 * @input: The input string to tokenize
 */
char **tokenizeInput(char *input)
{
	char *token;
	char **tokens = malloc(3 * sizeof(char *));

	if (tokens == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	token = strtok(input, " ");
	tokens[0] = token;
	token = strtok(NULL, " ");
	tokens[1] = token;

	tokens[2] = malloc(1);
	if (tokens[2] == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	tokens[2][0] = '\0';

	return (tokens);
}
/**
 *  execute_command - Execute command with the provided arguments
 *  Executes a command with the given arguments using fork and execvp.
 *  If the execution fails, it prints an error message and
 *  exits with failure status.
 *
 * @param args A null-terminated array of strings representing the
 * command and its arguments.
*/
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
			free(args);
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
