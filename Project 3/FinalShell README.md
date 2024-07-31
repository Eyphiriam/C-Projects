# README for Aggie Shell

This README provides a comprehensive overview of the Aggie Shell, a custom Unix shell implemented in C. The shell supports basic command execution, environment variable management, and batch processing. It is designed to help users interact with the operating system's services directly through a command-line interface.

## Project Overview

Aggie Shell is a simple yet functional Unix shell that allows users to execute commands, change directories, manage environment paths, and process batch scripts. It is implemented in C and utilizes system calls like `fork()`, `execvp()`, and `wait()` to manage processes. The shell operates in both interactive and batch modes, providing flexibility in how commands are executed.

## Features

- **Interactive Mode**: Directly type and execute commands.
- **Batch Mode**: Execute a series of commands from a file.
- **Built-in Commands**:
  - `cd`: Change the current working directory.
  - `path`: Set or get the system's PATH environment variable.
  - `exit`: Exit the shell.
- **Command Execution**: Execute external commands available in the system PATH.
- **Redirection**: Redirect the output of commands to files using the `>` operator.
- **Environment Variable Management**: Easily modify environment variables like PATH.

## Usage

### Interactive Mode

Run the shell without any arguments to start in interactive mode:

```bash
./aggie_shell
```

In this mode, you can type commands directly into the prompt:

```
ash /path/to/directory > command_to_execute
```

### Batch Mode

To start the shell in batch mode, provide a batch file as an argument:

```bash
./aggie_shell batch_file.txt
```

The shell will execute commands listed in `batch_file.txt` sequentially.

### Built-in Commands

- **Change Directory (`cd`)**:
  ```bash
  cd /path/to/directory
  ```
- **Manage PATH (`path`)**:
  - Set PATH:
    ```bash
    path /usr/local/bin:/usr/bin:/bin
    ```
  - Get current PATH:
    ```bash
    path
    ```
- **Exit the Shell (`exit`)**:
  ```bash
  exit
  ```

### Command Execution and Redirection

- Execute a command:
  ```bash
  ls -l
  ```
- Redirect output to a file:
  ```bash
  ls -l > output.txt
  ```

## Implementation Details

The shell is implemented in C and uses several POSIX APIs:

- **Process Management**: Uses `fork()` to create child processes and `execvp()` to execute commands.
- **Synchronization**: Uses `wait()` to wait for child processes to complete.
- **File Handling**: Uses `freopen()` to handle output redirection.
- **Error Handling**: Properly handles errors from system calls and provides meaningful error messages.

The shell's source code is organized into several files:

- **`main.c`**: Contains the main function and the shell's main loop.
- **`commands.c`**: Implements functions to handle built-in commands.
- **`batch.c`**: Handles the execution of commands from batch files.
