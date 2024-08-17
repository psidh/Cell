# Cell: A Basic Command-Line Shell in C

## Overview

This project is a basic implementation of a command-line shell in C

Supports `pwd`, `cd`, `ls`, and `echo`, as well as running external programs located in the `PATH` environment variable.

- **External Program Execution:**
  - Executes external programs and commands found in the `PATH` environment variable.
  - Supports running commands with arguments.

## Usage

1. **Compile the Program:**
   To compile the program, use:

   ```bash
   gcc -o my_shell main.c
   ```

2. **Run the Shell:**
   Start the shell by running:

   ```bash
   ./main
   ```

3. **Enter Commands:**
   At the prompt (`$ `), enter commands as you would in a typical shell. For example:

   - `pwd` to print the current directory.
   - `cd /path/to/directory` to change the directory.
   - `ls` to list files in the current directory.
   - `echo Hello World` to print "Hello World".
   - `type echo` to check if `echo` is a shell builtin.

4. **Exit the Shell:**
   To exit the shell, type:
   ```bash
   exit
   ```

## Error Handling

- If a command cannot be executed or a directory cannot be opened, appropriate error messages will be displayed.

## Example

Here is a sample interaction with the shell:

```bash
$ pwd
/home/user
$ cd /tmp
$ pwd
/tmp
$ ls
file1.txt
file2.txt
$ echo "Hello from /tmp"
Hello from /tmp
$ type ls
ls is /usr/bin/ls
$ exit
```
