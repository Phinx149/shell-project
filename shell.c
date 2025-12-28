#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

#define MAX_CMD_LEN 1024
#define MAX_ARGS 20

int main() {
    char path_name[MAX_CMD_LEN];
    char buffer[MAX_CMD_LEN];
    char *args[MAX_ARGS];
    
    while (1) {
        // Display current directory as prompt
        if (getcwd(path_name, MAX_CMD_LEN) == NULL) {
            perror("getcwd failed");
            exit(1);
        }
        printf("%s> ", path_name);
        
        // Read user input
        if (fgets(buffer, MAX_CMD_LEN, stdin) == NULL) {
            break;
        }
        
        // Remove newline
        buffer[strcspn(buffer, "\n")] = '\0';
        
        // Skip empty commands
        if (strlen(buffer) == 0) {
            continue;
        }
        
        // Parse command into arguments
        char *token = strtok(buffer, " ");
        int i = 0;
        while (token != NULL && i < MAX_ARGS - 1) {
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;
        
        // Handle built-in commands
        if (strcmp(args[0], "exit") == 0) {
            break;
        }
        
        if (strcmp(args[0], "cd") == 0) {
            if (args[1] == NULL) {
                fprintf(stderr, "cd: missing argument\n");
            } else {
                if (chdir(args[1]) != 0) {
                    perror("cd failed");
                }
            }
            continue;
        }
        
        // Execute external commands
        pid_t child = fork();
        
        if (child < 0) {
            perror("fork failed");
            exit(1);
        }
        
        if (child == 0) {
            // Child process
            if (execvp(args[0], args) == -1) {
                perror("command not found");
                exit(1);
            }
        } else {
            // Parent process
            wait(NULL);
        }
    }
    
    printf("Shell exiting...\n");
    return 0;
}
