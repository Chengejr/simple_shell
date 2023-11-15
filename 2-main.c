#include "shell.h"

/*
 * main - Entry point for the program
 *
 * Return: Always 0 (success)
 */
int main(void)
{
	char *input;
	char *command;
	char *arguments;
	char **args;

	while (1)
	{
		printPrompt();
		input = readInput();

		if (input == NULL)
		{
			write(STDOUT_FILENO, "\n", 1);
			free(input);
			break;
		}
		command = strtok(input, " ");
		arguments = strtok(NULL, " ");
		
		if (strcmp(command, "env") == 0)
		{
			printEnvironment();
			continue;
		}
		if (strcmp(command, "exit") == 0)
		{
			free(input);
			break;
		}
		
		if (arguments == NULL)
		{
			args = malloc(2 * sizeof(char*));
			
			if (args == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			args[0] = command;
			args[1] = NULL;
		}
		else
		{
			args = malloc(3 * sizeof(char*));
			if (args == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			args[0] = command;
			args[1] = arguments;
			args[2] = NULL;
		}
	
		executeCommand(args);
		free(input);
		free(args);
	}
	return (0);
}
