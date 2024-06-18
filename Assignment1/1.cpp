// Matthew Eyram Agboglo
// 9/12/2023
// COMP 350 - 001
// Creating a child process using the fork method also checking for errors.
#include <iostream>
#include <unistd.h>
using namespace std;



int main()
{

    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (child_pid > 0) {
        cout << "This is the parent process" << getpid()
             << endl;
    }
    else {
        cout << "This is the child process" << getpid()
             << endl;
    }

    return 0;
}