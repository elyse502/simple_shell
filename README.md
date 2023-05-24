# 0x16. C - Simple Shell
![eaa6f4c13eddb41293ec166ae76a5e0a](https://github.com/elyse502/simple_shell/assets/125453474/363c8910-a997-431a-9aed-146564f903a0)
# *SIMPLE SHELL*
* We created a basic version of the Unix shell from scratch. A program that takes commands from the keyboard and gives them to the operating system to perform. The shell can perform commands such as listing files in current working directory by typing `ls`, `exit`, among others. It works in both interactive and non-interactive mode.

* The following are the allowed functions and system calls;
  * `access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`,`free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, `stat`, `lstat`, `fstat`, `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, `write`.
* This simple shell is a Shell interface written in **C programming** language that gives to the user a prompt **_#cisfun$_** , after it accepts, it executes a user inputted command in a separate process called child process.

![68747470733a2f2f7365656b6c6f676f2e636f6d2f696d616765732f432f632d70726f6772616d6d696e672d6c616e67756167652d6c6f676f2d394233324430313742312d7365656b6c6f676f2e636f6d2e706e67](https://github.com/elyse502/simple_shell/assets/125453474/0df08bcc-e79f-4a1d-af7f-ed5ca95096f6)

# File Descriptions
* *__AUTHORS__*: Has the names of this project's contributors.
* **_execute.c**: Contains the function that executes shell commands.
* **_strings1.c**, **_strings2.c**, **_strings3.c**: Contains functions that are used to manipultate and get data about strings like finding string length and splitting a string.
* **built-in.c**: Includes functions to perform built-in shell command operations like `exit`.
* **main.h**: Holds all function prototypes and headers.
* **main.c**: The shell's entry point i.e contains the main method.
* **man_1_simple_shell**: A manual for the shell.
* **prompt.c**: Prints the shell's title to indicate the shell is ready to receive input.
* **readline**: Responsible for picking commands typed into the shell.
* **handle_path.c**: Contains functions used to handle cases when a command is entered into the shell instead of the path to the executable file. For example when a user types `ls` instead of `\bin\ls`;
## Builtin functions
List of builtin funtion supported by this simple shell:
| Buitin Function| Descriptions |
| :------------ |   :---:      |
| `env`      |Print current environment variables |
| `setenv`   |Set new environment variable `setenv var_name va_value` |
| `unsetenv` |Remove environment variable `unsetenv var_name va_value`|
## How to use the shell:
* Install;
```
(your_terminal)$ git clone <this repository>
(your_terminal)$ cd simple_shell
```
* Compile:
```
gcc -Wall -Werror -Wextra -pedantic *.c -o hsh
```
* Usage: non-interactive mode
```
echo "/bin/ls" | ./hsh
```
* Usage: interactive mode
```
(your_terminal)$ ./hsh
```
## Example
```
#cisfun$ /bin/ls -l
total 100
-rw-r--r-- 1 runner runner  2029 May 24 05:49 _env.c
-rw-r--r-- 1 runner runner  1052 May 19 13:26 _execute.c
-rw-r--r-- 1 runner runner  1767 May 19 13:27 _strings1.c
-rw-r--r-- 1 runner runner  1351 May 24 05:53 _strings2.c
-rw-r--r-- 1 runner runner  2516 May 19 13:29 _strings3.c
-rw-r--r-- 1 runner runner  2074 May 19 13:30 built-in.c
-rw-r--r-- 1 runner runner  1483 May 19 13:31 handle_path.c
-rwxr-xr-x 1 runner runner 44128 May 24 05:53 main
-rw-r--r-- 1 runner runner   752 May 19 13:21 main.c
-rw-r--r-- 1 runner runner  1225 May 19 13:22 main.h
-rw-r--r-- 1 runner runner  1520 May 24 05:48 man_1_simple_shell
-rw-r--r-- 1 runner runner   164 May 24 05:48 prompt.c
-rw-r--r-- 1 runner runner   506 May 19 13:32 readline.c

#cisfun$ exit
(your_terminal)$
```
## Bugs
At this time, there are no known bugs.

More info on our blog [here](https://www.tutorialspoint.com/unix/unix-what-is-shell.htm).

# _Authors_:
1. NIYIBIZI Elysée | [Github](https://github.com/elyse502).
2. MUHAYEMARIYA Faustine | [Github](https://github.com/faustine-van).

![68747470733a2f2f6173736574732e696d6167696e61626c65667574757265732e636f6d2f6d656469612f696d616765732f414c585f4c6f676f2e6d61782d323030783135302e706e67](https://github.com/elyse502/simple_shell/assets/125453474/abb84a4a-feba-4049-98c4-8f5001a4a635)

