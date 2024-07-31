#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>

#define MAX_INPUT_LENGTH 1024
#define MAX_ARGS 64
#define ERROR_MESSAGE "An error has occurred\n"

// Function to handle the exit built-in command
void handle_exit() {
    printf("Aggie Shell - Exiting...\n");
    exit(0);
}

// Function to handle the cd built-in command
void handle_cd(char* path) {
    if (path == NULL || strcmp(path, "") == 0) {
        fprintf(stderr, "Aggie Shell - cd: missing argument\n");
        return;
    }

    if (strcmp(path, "~") == 0) {
        path = getenv("HOME");
    }
    if (chdir(path) != 0) {
        fprintf(stderr, "Aggie Shell - cd: %s: No such file or directory\n", path);
    }
}

// Function to handle the path built-in command
void handle_path(char* args[]) {
    if (args[1] == NULL) {
        unsetenv("PATH");
    } else {
        char newPath[1024] = "";  // Adjust size as necessary
        for (int i = 1; args[i] != NULL; i++) {
            strcat(newPath, args[i]);
            if (args[i+1] != NULL) strcat(newPath, ":");
        }
        if (setenv("PATH", newPath, 1) != 0) {
            perror("Aggie Shell - setenv() error");
        }
    }
}

// Execute external commands
void execute_command(char *args[], char *outfile) {
    int pid = fork();
    if (pid == 0) { // Child process
        if (outfile != NULL) {
            int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
            if (fd == -1) {
                write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
                exit(1);
            }
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            close(fd);
        }
        if (execvp(args[0], args) == -1) {
            write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
            exit(1);
        }
    } else if (pid > 0) { // Parent process
        wait(NULL);
    } else {
        write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
    }
}

// Main shell loop
int main(int argc, char *argv[]) {
    FILE *stream = stdin;
    char *prompt = "ash > ";

    if (argc > 2) {
        write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
        exit(1);
    }

    if (argc == 2) {
        stream = fopen(argv[1], "r");
        if (!stream) {
            write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
            exit(1);
        }
        prompt = "";
    }

    char input[MAX_INPUT_LENGTH];
    char *args[MAX_ARGS];
    char *outfile = NULL;

    while (1) {
        printf("%s", prompt);
        fflush(stdout);

        if (fgets(input, MAX_INPUT_LENGTH, stream) == NULL) {
            if (feof(stream)) {
                exit(0);
            }
            write(STDERR_FILENO, ERROR_MESSAGE, strlen(ERROR_MESSAGE));
            continue;
        }

        input[strcspn(input, "\n")] = 0; // Remove newline character
        char *token = strtok(input, " ");
        int i = 0;

        while (token != NULL) {
            if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " ");
                outfile = token;
                break;
            }
            args[i++] = token;
            token = strtok(NULL, " ");
        }
        args[i] = NULL;

        if (args[0] == NULL) continue; // Empty command

        if (strcmp(args[0], "exit") == 0) {
            handle_exit();
        } else if (strcmp(args[0], "cd") == 0) {
            handle_cd(args[1]);
        } else if (strcmp(args[0], "path") == 0) {
            handle_path(args);
        } else {
            execute_command(args, outfile);
        }
    }

    return 0;
}
