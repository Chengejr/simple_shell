#ifndef SHELL_H
#define SHELL_H

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
extern char **environ;

#define MAX_INPUT_SIZE 1024

void handle_arguments(void);
void parse_command(const char *command, char *args[]);
void printPrompt();
char* readInput();
void printEnvironmentLine(const char *env);
void printEnvironment();
char** tokenizeInput(char *input);
void executeCommand(char **args);
void changeDirectory(const char *path);
#endif
