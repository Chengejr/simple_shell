#include "shell.h"

int main(void)
{	char *input;
	char **tokens;
	char *command;

	while (1)
	{
		printPrompt();
		input = readInput();
		tokens = tokenizeInput(input);
		command = tokens[0];
		
		if (strcmp(command, "env") == 0)
		{
			printEnvironment();
			continue;
		}

		executeCommand(tokens);
		free(tokens);
	}
	return (0);
}

