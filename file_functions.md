
# OS ASSIGNMENT 3

## Aim

Implement a shell which supports semi-colon separated list of commands.

## How to run

Run the following commands in the terminal

```
make
./shell
```

## Files used

### shell.h

A header file containing the function prototypes and global variables

### main.c

The main file, contains the code to run the main infinite loop for the shell. It also displays the finished background processes by checking for signals that indicate whether the child is dead or not. 

### display_shell_prompt.c

This file contains the code to display the shell prompt as <username@system_name:curr_dir> 

### string_splitter.c

This file contains the code to parse the string, i.e. break down a long string into substrings, based on a separator. (used in interpret_cmd)

### interpret_cmd.c

This file contains the code to interpret the command, i.e. the line entered. It parses the line entered into different commands on the basis of semicolons. Then if it contains a pipe, it is executed by a pipe_handler. Otherwise break into different arguments based on spaces. In case, the command entered is exit, echo or pwd, the command is executed without calling any external function. For other built-ins, like cd, ls and pinfo, external functions are used. It also executes external commands using exec in both foreground and background manner. It also handles redirection using a redirect_handler function

### exec_cd.c

This file implements cd command in the shell.

### exec_ls.c

This file implements ls command in the shell.
Accepted tags: -l -a -la -al

### exec_pinfo.c

This file implements pinfo command in the shell.

### exec_env.c

This file implements setenv and unsetenv commands in the shell.

### exec_fg_bg_kjob.c

This file implements fg, bg and kjob commands in the shell.

### exec_jobs.c

This file implements jobs commands in the shell.

### exec_cronjob.c

This file implements cronjob commands in the shell.

### pipe_handler.c

This file handles the pipes if given in the command.

### redirect_handler.c

This file handles the redirection symbols if given in the command.

### get_status.c

This file contains the function that returns the status of any running process, given its pid.

### isvalid_redirection.c

This file checks if the given command is valid (with respect to the redirection symbols)
