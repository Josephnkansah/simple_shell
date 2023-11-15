#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_COMMAND_LENGTH 100
#define MAX_ARGUMENTS 10

int main() {
    char command[MAX_COMMAND_LENGTH];
    char *arguments[MAX_ARGUMENTS];
    char *token;

    while (1) {
        printf("SimpleShell> ");
        fgets(command, sizeof(command), stdin);

        // Remove the newline character from the command
        command[strcspn(command, "\n")] = '\0';

        // Tokenize the input command
        int i = 0;
        token = strtok(command, " ");
        while (token != NULL && i < MAX_ARGUMENTS - 1) {
            arguments[i++] = token;
            token = strtok(NULL, " ");
        }
        arguments[i] = NULL; // Null-terminate the argument list

        if (strcmp(arguments[0], "exit") == 0) {
            printf("Exiting the shell...\n");
            break;
        }

        pid_t pid = fork();

        if (pid == -1) {
            // Fork failed
            perror("fork");
        } else if (pid == 0) {
            // Child process
            execvp(arguments[0], arguments);
            // If execvp returns, it means there was an error
            perror("execvp");
            exit(EXIT_FAILURE);
        } else {
            // Parent process
            wait(NULL); // Wait for the child to finish
        }
    }

    return 0;
}
