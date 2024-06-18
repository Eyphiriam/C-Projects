#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

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
        char cwd[MAX_INPUT_LENGTH];
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

// Function to handle batch processing
void handle_batch(char* filename) {
    FILE *batch_file;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    batch_file = fopen(filename, "r");
    if (batch_file == NULL) {
        fprintf(stderr, "Aggie Shell - Error opening batch file: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, batch_file)) != -1) {
        printf("Retrieved line of length %zu :\n", read);
        printf("%s", line);
        // Execute the command
        system(line);
    }

    fclose(batch_file);
    if (line)
        free(line);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // Batch mode
        handle_batch(argv[1]);
    } else {
        // Interactive mode
        while (1) {
            char cwd[MAX_INPUT_LENGTH];
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
                char *path = input + 3;
                handle_cd(path);
                continue; // Continue to the next iteration of the loop
            }

            // Check if the command is "path"
            if (strncmp(input, "path ", 5) == 0) {
                char *new_path = input + 5;
                handle_path(new_path);
                continue; // Continue to the next iteration of the loop
            }

            // Split the input into command and arguments
            char *command = strtok(input, " ");
            char *arguments[MAX_INPUT_LENGTH];
            int i = 0;
            while (command != NULL) {
                arguments[i++] = command;
                command = strtok(NULL, " ");
            }
            arguments[i] = NULL; // Set the last element to NULL

            // Check if there is a ">" symbol in the arguments
            int redirect_index = -1;
            for (int j = 0; j < i; j++) {
                if (strcmp(arguments[j], ">") == 0) {
                    redirect_index = j;
                    break;
                }
            }

            if (redirect_index != -1) {
                // Redirect output to a file
                char *filename = arguments[redirect_index + 1];
                FILE *file = freopen(filename, "w", stdout);
                if (file == NULL) {
                    perror("Aggie Shell - freopen() error");
                    exit(1);
                }

                // Execute the command
                arguments[redirect_index] = NULL; // Set the ">" symbol to NULL
                execvp(arguments[0], arguments);
                perror("Aggie Shell - execvp() error");
                exit(1);
            } else {
                // No redirection, execute the command as usual
                pid_t pid = fork();
                if (pid == 0) {
                    // Child process
                    execvp(arguments[0], arguments);
                    perror("Aggie Shell - execvp() error");
                    exit(1);
                } else if (pid < 0) {
                    // Error occurred
                    perror("Aggie Shell - fork() error");
                } else {
                    // Parent process
                    wait(NULL); // Wait for the child to exit
                }
            }
        }
    }
}
