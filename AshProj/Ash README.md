# Comprehensive README for AshProj (Aggie Shell Project)

This README provides a detailed overview of the AshProj, a simple Unix shell designed to familiarize users with Unix/Linux programming environments, process management, and shell functionalities.

## Table of Contents

1. [Project Overview](#project-overview)
2. [Features](#features)
3. [Built-in Commands](#built-in-commands)
4. [Testing](#testing)

## Project Overview

The AshProj, short for Aggie Shell, is a command-line interpreter designed to emulate basic functionalities of a Unix shell. It operates in both interactive and batch modes, allowing users to execute commands directly or from a script file.

## Features

- **Interactive Mode**: Directly type commands into the shell prompt.
- **Batch Mode**: Execute commands from a batch file.
- **Built-in Commands**: Includes `exit`, `cd`, and `path`.
- **External Command Execution**: Executes system commands located in the system's PATH.
- **Redirection**: Supports redirection of standard output and standard error to files.
- **Error Handling**: Provides a uniform error message for exceptions not handled by external commands.

## Built-in Commands

- `exit`: Exits the shell.
- `cd [directory]`: Changes the current working directory.
- `path [directory list]`: Sets the search path for executable files.

## Testing

Testing involves checking the functionality of built-in commands, external command execution, and error handling. Create test scripts or manually enter commands to ensure all features work as expected.
