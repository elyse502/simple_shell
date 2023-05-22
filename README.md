# 0x16. C - Simple Shell
![eaa6f4c13eddb41293ec166ae76a5e0a](https://github.com/elyse502/simple_shell/assets/125453474/363c8910-a997-431a-9aed-146564f903a0)
# *SIMPLE SHELL*
* We created a basic version of the Unix shell from scratch. A program that takes commands from the keyboard and gives them to the operating system to perform. The shell can perform commands such as listing files in current working directory by typing `ls`, `exit`, among others. It works in both interactive and non-interactive mode.

* The following are the allowed functions and system calls;
  * `access`, `chdir`, `close`, `closedir`, `execve`, `exit`, `_exit`, `fflush`, `fork`,`free`, `getcwd`, `getline`, `getpid`, `isatty`, `kill`, `malloc`, `open`, `opendir`, `perror`, `read`, `readdir`, `signal`, `stat`, `lstat`, `fstat`, `strtok`, `wait`, `waitpid`, `wait3`, `wait4`, `write`.
* This simple shell is a Shell interface written in **C programming** language that gives to the user a prompt *#cisfun$*, after it accepts, it executes a user inputted command in a separate process called child process.

![68747470733a2f2f7365656b6c6f676f2e636f6d2f696d616765732f432f632d70726f6772616d6d696e672d6c616e67756167652d6c6f676f2d394233324430313742312d7365656b6c6f676f2e636f6d2e706e67](https://github.com/elyse502/simple_shell/assets/125453474/0df08bcc-e79f-4a1d-af7f-ed5ca95096f6)

# File Descriptions
* *__AUTHORS__*: Has the names of this project's contributors.
* **execute**: Contains the function that executes shell commands.
* **_strings1.c**, **_strings2.c**, **_strings3.c**: Contains functions that are used to manipultate and get data about strings like finding string length and splitting a string.
* **built-in.c**: Includes functions to perform built-in shell command operations like `exit`.
* **main.h**: Holds all function prototypes and headers.
* **main.c**: The shell's entry point i.e contains the main method.
* **man_1_simple_shell**: A manual for the shell.
* **prompt.c**: Prints the shell's title to indicate the shell is ready to receive input.
* **readline**: Responsible for picking commands typed into the shell.
* **handle_path.c**: Contains functions used to handle cases when a command is entered into the shell instead of the path to the executable file. For example when a user types `ls` instead of `\bin\ls`;
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
total 68
-rw-rw-r-- 1 vagrant vagrant   168 Aug 15 06:39 AUTHORS
-rw-rw-r-- 1 vagrant vagrant  1761 Aug 21 06:59 README.md
-rw-rw-r-- 1 vagrant vagrant   887 Aug 20 10:27 _execute.c

#cisfun$ exit 100
(your_terminal)$
```
## Bugs
At this time, there are no known bugs.

More info on our blog [here](https://medium.com/@muxanz/how-the-shell-works-internally-when-entering-a-command-42f08458870)

# _Authors_:
1. NIYIBIZI Elysée | [Github](https://github.com/elyse502).
2. MUHAYEMARIYA Faustine | [Github](https://github.com/faustine-van).

![68747470733a2f2f6173736574732e696d6167696e61626c65667574757265732e636f6d2f6d656469612f696d616765732f414c585f4c6f676f2e6d61782d323030783135302e706e67](https://github.com/elyse502/simple_shell/assets/125453474/abb84a4a-feba-4049-98c4-8f5001a4a635)

