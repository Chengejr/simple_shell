#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

#define MAX_COMMAND_LENGTH 256

int main() {
    char command[MAX_COMMAND_LENGTH];
    size_t command_length;
    pid_t pid;

    while (1) {
        printf("simple_shell> ");
        if (fgets(command, sizeof(command), stdin) == NULL) {
            printf("\n"); /* Handle Ctrl+D (End of File) */
            break;
        }

        /* Remove the newline character from the command */
        command_length = strlen(command);
        if (command_length > 0 && command[command_length - 1] == '\n') {
            command[command_length - 1] = '\0';
        }

        /* Fork a child process to execute the command */
        pid = fork();
        if (pid < 0) {
            perror("Fork error");
        } else if (pid == 0) {
            /* Child process */
            int result = execlp(command, command, NULL);
            if (result == -1) {
                printf("Command not found: %s\n", command);
                exit(1);
            }
        } else {
            /* Parent process */
            int status;
            wait(&status);
        }
    }

    return 0;
}
