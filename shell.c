#include "shell.h"

/**
 * main - Main function  allows
 * the user to enter commands for execution.
 *
 * This function provides a basic shell interface where the user
 * can enter commands. The shell will execute the entered commands
 * and display the output, if any. It supports simple commands and
 * does not include advanced features such as piping, redirection, etc.
 */

int main(void)
{
    char *command = NULL;
    size_t bufsize = 0;
    char *args[2];
    pid_t pid;
    int status;

    while (1)
    {
        write(STDOUT_FILENO, "$", 2);
        if (getline(&command, &bufsize, stdin) == -1)
        {
            write(STDOUT_FILENO, "\n", 1);
            free(command);
            break;
        }

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
    free(command);
    return (0);
}

