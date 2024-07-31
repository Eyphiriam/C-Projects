This shell allows users to interact with the operating system via a command-line interface, executing built-in commands such as `exit`, `cd` (change directory), and `path` (to get or set the system path). Below is a detailed explanation of the code, which can be used to enhance the README file for clarity and completeness.

### Overview of the Aggie Shell Code

The Aggie Shell operates in an infinite loop, continuously prompting the user for commands and processing them accordingly. Here's a breakdown of the key components and functionalities:

1. **Global Definitions and Includes**:
   - `MAX_INPUT_LENGTH`: Defines the maximum length for user input.
   - Standard C libraries are included for file and string operations, and for system calls.

2. **Built-in Command Functions**:
   - `handle_exit()`: Exits the shell with a message.
   - `handle_cd(char* path)`: Changes the current working directory. It handles the special case for the home directory (`~`) and prints errors if the directory change fails.
   - `handle_path(char* new_path)`: Either prints the current path or sets a new path for the environment variable `PATH`.

3. **Main Function**:
   - **Command Prompt**: Displays the current working directory as part of the prompt.
   - **Input Handling**: Reads user input and removes the newline character.
   - **Command Processing**:
     - Checks if the command is `exit` and calls `handle_exit()`.
     - Checks if the command starts with `cd ` and calls `handle_cd()` with the appropriate path.
     - Checks if the command starts with `path ` and calls `handle_path()` with the new path.

### Detailed Functionality

- **Exiting the Shell**: When the user types `exit`, the `handle_exit()` function is called, which prints a closing message and terminates the program.
- **Changing Directories**: The `handle_cd()` function allows the user to change the current directory. It handles edge cases like missing arguments and attempts to change to the home directory using the `~` symbol.
- **Managing PATH**: The `handle_path()` function is used to either display the current `PATH` environment variable or to set it to a new value, depending on whether an argument is provided.

### Usage in the Shell

- To **change the directory** to `/usr`, the user would type:
  ```
  cd /usr
  ```
- To **view the current path** or **set a new path**, the user would type:
  ```
  path
  path /usr/local/bin:/usr/bin
  ```
- To **exit the shell**, the user simply types:
  ```
  exit
  ```
