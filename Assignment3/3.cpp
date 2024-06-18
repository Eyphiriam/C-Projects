// Matthew Eyram Agboglo
// 9/24/2023
// COMP 350 - 001
// Executing inter process communication and redirection. By using pipe() and  dup(). include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc < 2) {
        cerr << "No command provided" << endl;
        return 1;
    }

    int fd[2];
    pid_t pid;
    char *command = argv[1];
    char *args[] = {command, nullptr};
    bool outputToFile = false;
    bool outputToMonitor = false;

    // Check for optional arguments
    for (int i = 2; i < argc; i++) {
        if (string(argv[i]) == "-o") {
            outputToFile = true;
        } else if (string(argv[i]) == "-b") {
            outputToFile = true;
            outputToMonitor = true;
        }
    }

    // Create a pipe
    if (pipe(fd) == -1) {
        cerr << "Pipe failed" << endl;
        return 1;
    }

    // Fork a child process
    pid = fork();

    // Check if fork was successful
    if (pid < 0) {
        cerr << "Fork failed" << endl;
        return 1;
    }

    if (pid == 0) { // Child process
        close(fd[0]); // Close reading end in the child
        dup2(fd[1], STDOUT_FILENO); // Send stdout to the pipe
        close(fd[1]); // This descriptor is no longer needed

        // Execute the command
        if (execvp(command, args) < 0) {
            cerr << "Exec failed" << endl;
            return 1;
        }
    } else { // Parent process
        char buffer[1024];
        close(fd[1]); // Close writing end in the parent

        // Open output.txt file if output is to be redirected to file
        int file = -1;
        if (outputToFile) {
            file = open("output.txt", O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (file < 0) {
                cerr << "File open failed" << endl;
                return 1;
            }
        }

        // Redirect stdout to output.txt if output is to be redirected to file
        if (outputToFile && !outputToMonitor) {
            dup2(file, STDOUT_FILENO);
        }

        // Read from pipe and write to stdout (which is now output.txt) and/or monitor
        ssize_t count;
        while ((count = read(fd[0], buffer, sizeof(buffer))) != 0) {
            if (outputToFile) {
                write(file, buffer, count);
            }
            if (outputToMonitor) {
                write(STDOUT_FILENO, buffer, count);
            }
        }

        close(fd[0]);
        if (outputToFile) {
            close(file);
        }
    }

    return 0;
}
