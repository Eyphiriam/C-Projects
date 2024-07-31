#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_INPUT_LENGTH 100

// Function to handle the exit built-in command
void handle_exit() {
    printf("Aggie Shell - Exiting...\n");
    exit(0);
}

// Function to handle the cd built-in command
void handle_cd(char* path) {
    if (path == NULL) {
        fprintf(stderr, "Aggie Shell - cd: missing argument\n");
        return;
    }

    if (strcmp(path, "~") == 0) {
        path = getenv("HOME");
        if (path == NULL) {
            fprintf(stderr, "Aggie Shell - cd: HOME not set\n");
            return;
        }
        printf("Aggie Shell - cd: Changing to home directory: %s\n", path);
    }
    if (chdir(path) != 0) {
        fprintf(stderr, "Aggie Shell - cd: %s: No such file or directory\n", path);
    }
}

// Function to handle the path built-in command
void handle_path(char* new_path) {
    if (new_path == NULL) {
        // Print the current path
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("Aggie Shell - Current path: %s\n", cwd);
        } else {
            perror("Aggie Shell - getcwd() error");
        }
    } else {
        // Set the new path
        if (setenv("PATH", new_path, 1) != 0) {
            perror("Aggie Shell - setenv() error");
        }
    }
}

int main() {
    while (1) {
        char cwd[1024];
        if (getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("ash %s > ", cwd);
        } else {
            perror("getcwd() error");
        }

        // Read the user input
        char input[MAX_INPUT_LENGTH];
        fgets(input, sizeof(input), stdin);

        // Remove the newline character from the input
        input[strcspn(input, "\n")] = '\0';

        // Check if the command is "exit"
        if (strcmp(input, "exit") == 0) {
            handle_exit();
            break; // Exit the loop and terminate the shell
        }

        // Check if the command is "cd"
        if (strncmp(input, "cd ", 3) == 0) {
            char* path = input + 3;
            handle_cd(path);
            continue; // Continue to the next iteration of the loop
        }

        // Check if the command is "path"
        if (strncmp(input, "path ", 5) == 0) {
            char* new_path = input + 5;
            handle_path(new_path);
        }

    


    }
    return 0;
}
