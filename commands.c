#include "shell.h"

/**
 * executeCommand - Executes a given command.
 * @command: The command to execute.
 *
 * Return: void.
 */
void executeCommand(char *command) {
    pid_t pid; 
    char *argv[2]; 

    char *newline = strchr(command, '\n');
    if (newline) *newline = '\0';

    if (strcmp(command, "exit") == 0) {
        exit(EXIT_SUCCESS);
    }

    if (access(command, X_OK) == -1) {
        write(STDERR_FILENO, command, strlen(command));
        write(STDERR_FILENO, ": No such file or directory\n", 28);
        return;
    }

    
    pid = fork(); 
    if (pid == -1) {
        perror("fork");
        return;
    }
    if (pid == 0) {
       
        argv[0] = command; 
        argv[1] = NULL;   
        if (execve(command, argv, environ) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        wait(NULL);
    }
}
