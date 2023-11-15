#include "shell.h"

int main(void) {
    char *input = NULL;
    char *command;
    char *arguments;
    pid_t pid;
    char **args;
    size_t len = 0;
    ssize_t read;
    size_t input_length;

    while (1) {
        /* Print the shell prompt */
        write(STDOUT_FILENO, "$ ", 2);

        /* Read the input from the user */
        read = getline(&input, &len, stdin);

        if (read == -1) {
            /* If the end of file is reached, exit the shell */
            write(STDOUT_FILENO, "\n", 1);
            free(input);
            break;
        }

        /* Remove the newline character from the input */
        input_length = strlen(input);
        if (input_length > 0 && input[input_length - 1] == '\n') {
            input[input_length - 1] = '\0';
        }

        /* Split the input into command and arguments */
        command = strtok(input, " ");
        arguments = strtok(NULL, " ");

        pid = fork();

        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            
            if (arguments == NULL) {
                args = malloc(2 * sizeof(char *));
                if (args == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                args[0] = (char *)command;
                args[1] = NULL;
            } else {
                args = malloc(3 * sizeof(char *));
                if (args == NULL) {
                    perror("malloc");
                    exit(EXIT_FAILURE);
                }
                args[0] = (char *)command;
                args[1] = (char *)arguments;
                args[2] = NULL;
            }
            executeCommand(args);
            free(args);
            exit(EXIT_SUCCESS);
        } else {
            
            int status;

            waitpid(pid, &status, 0);
        }
    }

    return 0;
}

