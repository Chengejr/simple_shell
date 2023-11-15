#include "shell.h"

void printEnvironmentLine(const char *env)
{
	size_t env_length = strlen(env);

	write(STDOUT_FILENO, env, env_length);
	write(STDOUT_FILENO, "\n", 1);
}

void printEnvironment(void)
{
	char **env = environ;

	while (*env)
	{
		printEnvironmentLine(*env);
		env++;
	}
}
void changeDirectory(const char *path)
{
	if (path == NULL || strcmp(path, "..") == 0)
	{
		if (chdir("..") == -1)
		{
			perror("chdir");
		}
	}
	else
	{
		if (chdir(path) == -1)
		{
			perror("chdir");
		}
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
		exit(EXIT_SUCCESS);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
