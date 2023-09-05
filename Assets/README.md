# shellby - Simple Shell 🐚
A simple UNIX command interpreter written as part of the low-level programming and algorithm track at Holberton School.

## Description 💬
Shellby is a simple UNIX command language interpreter that reads commands from either a file or standard input and executes them.

# Concepts
_For this project, we expect you to look at these concepts:_
* [Everything you need to know to start coding your own shell](https://intranet.alxswe.com/concepts/64)
* [Approaching a Project](https://intranet.alxswe.com/concepts/350)

# 1. Everything you need to know to start coding your own shell
## PID & PPID
A process is an instance of an executing program, that has a unique process ID. This process ID is used by many functions and system calls to interact with and manipulate processes. In order to retrieve the current process’ ID, you can use the system call `getpid` (man 2 `getpid`):
```
julien@ubuntu:~/c/shell$ cat pid.c
#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;

    my_pid = getpid();
    printf("%u\n", my_pid);
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Werror -pedantic pid.c -o mypid && ./mypid
3237
julien@ubuntu:~/c/shell$ ./mypid 
3238
julien@ubuntu:~/c/shell$ ./mypid 
3239
julien@ubuntu:~/c/shell$
```
Note in the example above, that every time you run the program, a new process is created, and its ID is different.

Each process has a parent: the process that created it. It is possible to get the PID of a parent process by using the `getppid` system call (man 2 `getppid`), from within the child process.

## Exercises
#### 0. getppid
Write a program that prints the PID of the parent process. Run your program several times within the same shell. It should be the same. Does `echo $$` print the same value? Why?

#### 1. /proc/sys/kernel/pid_max
Write a shell script that prints the maximum value a process ID can be.

# Arguments
The command line arguments are passed through the `main` function: `int main(int ac, char **av);`
* `av` is a `NULL` terminated array of strings
* `ac` is the number of items in `av`

`av[0]` usually contains the name used to invoke the current program. `av[1]` is the first argument of the program, `av[2]` the second, and so on.

## Exercises
#### 0. av
Write a program that prints all the arguments, without using `ac`.

#### 1. Read line
Write a program that prints `"$ "`, wait for the user to enter a command, prints it on the next line.

man 3 `getline`

**important** make sure you read the man, and the RETURN VALUE section, in order to know when to stop reading Keyword: “end-of-file”, or `EOF` (or `Ctrl+D`).

#advanced: Write your own version of `getline`.
```
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic prompt.c -o prompt
julien@ubuntu:~/c/shell$ ./prompt 
$ cat prompt.c
cat prompt.c
julien@ubuntu:~/c/shell$
```
#### 2. command line to av
Write a function that splits a string and returns an array of each word of the string.

man `strtok`

_#advanced_: Write the function without `strtok`

## Executing a program
The system call `execve` allows a process to execute another program (man 2 `execve`). Note that this system call does load the new program into the current process’ memory in place of the “previous” program: on success `execve` does not return to continue the rest of the “previous” program.

### Warning: in this example, `execve` is used without the current environment (last argument), don’t forget to add it in your Shell!
```
julien@ubuntu:~/c/shell$ cat exec.c
#include <stdio.h>
#include <unistd.h>

/**
 * main - execve example
 *
 * Return: Always 0.
 */
int main(void)
{
    char *argv[] = {"/bin/ls", "-l", "/usr/", NULL};

    printf("Before execve\n");
    if (execve(argv[0], argv, NULL) == -1)
    {
        perror("Error:");
    }
    printf("After execve\n");
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic exec.c -o exec
julien@ubuntu:~/c/shell$ ./exec 
Before execve
total 120
drwxr-xr-x   2 root root 61440 Dec  4 00:08 bin
drwxr-xr-x   2 root root  4096 Jul 19 13:47 games
drwxr-xr-x  58 root root  4096 Oct 27 13:10 include
drwxr-xr-x 138 root root  4096 Dec  4 00:08 lib
drwxr-xr-x   3 root root  4096 Nov 10 09:54 lib32
drwxr-xr-x   3 root root  4096 Nov 10 09:54 libx32
drwxr-xr-x  10 root root  4096 Jul 19 13:42 local
drwxr-xr-x   3 root root  4096 Jul 19 13:48 locale
drwxr-xr-x   2 root root 12288 Dec  2 11:03 sbin
drwxr-xr-x 295 root root 12288 Jul 27 08:58 share
drwxr-xr-x   6 root root  4096 Dec  1 11:39 src
julien@ubuntu:~/c/shell$
```
## Creating processes
The system call `fork` (man 2 `fork`) creates a new child process, almost identical to the parent (the process that calls `fork`). Once `fork` successfully returns, two processes continue to run the same program, but with different stacks, datas and heaps.
```
julien@ubuntu:~/c/shell$ cat fork.c
#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t pid;

    printf("Before fork\n");
    pid = fork();
    if (pid == -1)
    {
        perror("Error:");
        return (1);
    }
    printf("After fork\n");
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    return (0);
}
julien@ubuntu:~/c/shell$ ./fork 
Before fork
After fork
My pid is 4819
julien@ubuntu:~/c/shell$ After fork
My pid is 4820
```
_Note: there is no typo in the above example_

Using the return value of `fork`, it is possible to know if the current process is the father or the child: `fork` will return `0` to the child, and the PID of the child to the father.
```
julien@ubuntu:~/c/shell$ cat fork.c
#include <stdio.h>
#include <unistd.h>

/**
 * main - fork example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t my_pid;
    pid_t child_pid;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return (1);
    }
    my_pid = getpid();
    printf("My pid is %u\n", my_pid);
    if (child_pid == 0)
    {
        printf("(%u) Nooooooooo!\n", my_pid);
    }
    else
    {
        printf("(%u) %u, I am your father\n", my_pid, child_pid);
    }
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic fork.c -o fork
julien@ubuntu:~/c/shell$ ./fork 
My pid is 4869
(4869) 4870, I am your father
julien@ubuntu:~/c/shell$ My pid is 4870
(4870) Nooooooooo!
```
## Wait
The `wait` system call (man 2 `wait`) suspends execution of the calling process until one of its children terminates.
```
julien@ubuntu:~/c/shell$ cat wait.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - fork & wait example
 *
 * Return: Always 0.
 */
int main(void)
{
    pid_t child_pid;
    int status;

    child_pid = fork();
    if (child_pid == -1)
    {
        perror("Error:");
        return (1);
    }
    if (child_pid == 0)
    {
        printf("Wait for me, wait for me\n");
        sleep(3);
    }
    else
    {
        wait(&status);
        printf("Oh, it's all better now\n");
    }
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Wextra -Werror -pedantic wait.c -o wait
julien@ubuntu:~/c/shell$ ./wait 
Wait for me, wait for me
Oh, it's all better now
julien@ubuntu:~/c/shell$
```
## Exercise: fork + wait + execve
Write a program that executes the command `ls -l /tmp` in 5 different child processes. Each child should be created by the same process (the father). Wait for a child to exit before creating a new child.

## Exercise: super simple shell
Using everything we saw, write a first version of a super simple shell that can run commands with their full path, without any argument.
```
julien@ubuntu:~/c/shell$ l
total 140
drwxrwxr-x  2 julien julien 4096 Dec  4 20:55 .
drwxrwxr-x 17 julien julien 4096 Dec  4 13:04 ..
-rw-rw-r--  1 julien julien  249 Dec  4 13:15 env-environ.c
-rw-rw-r--  1 julien julien  231 Dec  4 13:09 env-main.c
-rwxrwxr-x  1 julien julien 8768 Dec  4 19:52 exec
-rw-rw-r--  1 julien julien  302 Dec  4 19:38 exec.c
-rwxrwxr-x  1 julien julien 8760 Dec  4 20:11 fork
-rw-rw-r--  1 julien julien  438 Dec  4 19:57 fork.c
-rwxrwxr-x  1 julien julien 8656 Dec  4 13:45 mypid
-rw-rw-r--  1 julien julien  179 Dec  4 19:49 pid.c
-rwxrwxr-x  1 julien julien 8656 Dec  4 13:48 ppid
-rw-rw-r--  1 julien julien  180 Dec  4 13:48 ppid.c
-rwxrwxr-x  1 julien julien 8680 Dec  4 13:44 printenv
-rwxrwxr-x  1 julien julien 8760 Dec  4 14:38 prompt
-rwxrwxr-x  1 julien julien 8760 Dec  4 14:38 promptc
-rw-rw-r--  1 julien julien  191 Dec  4 14:17 prompt.c
-rw-rw-r--  1 julien julien  753 Dec  4 20:49 shell.c
-rwxrwxr-x  1 julien julien 8864 Dec  4 20:38 wait
-rw-rw-r--  1 julien julien  441 Dec  4 20:15 wait.c
julien@ubuntu:~/c/shell$ gcc -Wall -Werror -pedantic shell.c -o shell
julien@ubuntu:~/c/shell$ ./shell 
#cisfun$ /bin/ls
env-environ.c  exec    fork    mypid  ppid    printenv  promptc   shell    wait
env-main.c     exec.c  fork.c  pid.c  ppid.c  prompt    prompt.c  shell.c  wait.c
#cisfun$ ./ppid
5451
#cisfun$ ./ppid
5451
#cisfun$ ^C
julien@ubuntu:~/c/shell$
```
## File information
The `stat` (man 2 stat) system call gets the status of a file. On success, zero is returned. On error, -1 is returned.
```
julien@ubuntu:~/c/shell$ cat stat.c
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

/**
 * main - stat example
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
    unsigned int i;
    struct stat st;

    if (ac < 2)
    {
        printf("Usage: %s path_to_file ...\n", av[0]);
        return (1);
    }
    i = 1;
    while (av[i])
    {
        printf("%s:", av[i]);
        if (stat(av[i], &st) == 0)
        {
            printf(" FOUND\n");
        }
        else
        {
            printf(" NOT FOUND\n");
        }
        i++;
    }
    return (0);
}
julien@ubuntu:~/c/shell$ ./stat ls /bin/ls /usr/bin/ls
ls: NOT FOUND
/bin/ls: FOUND
/usr/bin/ls: NOT FOUND
julien@ubuntu:~/c/shell$
```
## Exercise: find a file in the PATH
Write a program that looks for files in the current PATH.
* Usage: `_which filename ...`

## Environment
We have seen earlier that the shell uses an environment list, where environment variables are “stored”. The list is an array of strings, with the following format: `var=value`, where `var` is the name of the variable and value its `value`. As a reminder, you can list the environment with the command `printenv`:
```
julien@ubuntu:~/c/shell$ printenv
XDG_VTNR=7
XDG_SESSION_ID=c2
CLUTTER_IM_MODULE=xim
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/julien
SESSION=ubuntu
GPG_AGENT_INFO=/home/julien/.gnupg/S.gpg-agent:0:1
TERM=xterm-256color
SHELL=/bin/bash
XDG_MENU_PREFIX=gnome-
VTE_VERSION=4205
QT_LINUX_ACCESSIBILITY_ALWAYS_ON=1
WINDOWID=23068682
UPSTART_SESSION=unix:abstract=/com/ubuntu/upstart-session/1000/1558
GNOME_KEYRING_CONTROL=
GTK_MODULES=gail:atk-bridge:unity-gtk-module
USER=julien
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
QT_ACCESSIBILITY=1
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
SESSION_MANAGER=local/ubuntu:@/tmp/.ICE-unix/1792,unix/ubuntu:/tmp/.ICE-unix/1792
DEFAULTS_PATH=/usr/share/gconf/ubuntu.default.path
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/usr/share/upstart/xdg:/etc/xdg
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DESKTOP_SESSION=ubuntu
QT_IM_MODULE=ibus
QT_QPA_PLATFORMTHEME=appmenu-qt5
XDG_SESSION_TYPE=x11
JOB=dbus
PWD=/home/julien/c/shell_course
XMODIFIERS=@im=ibus
GNOME_KEYRING_PID=
LANG=en_US.UTF-8
GDM_LANG=en_US
MANDATORY_PATH=/usr/share/gconf/ubuntu.mandatory.path
IM_CONFIG_PHASE=1
COMPIZ_CONFIG_PROFILE=ubuntu
GDMSESSION=ubuntu
SESSIONTYPE=gnome-session
GTK2_MODULES=overlay-scrollbar
XDG_SEAT=seat0
HOME=/home/julien
SHLVL=1
LANGUAGE=en_US
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
XDG_SESSION_DESKTOP=ubuntu
LOGNAME=julien
QT4_IM_MODULE=xim
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-jH9kfagEpM
LESSOPEN=| /usr/bin/lesspipe %s
INSTANCE=
XDG_RUNTIME_DIR=/run/user/1000
DISPLAY=:0
XDG_CURRENT_DESKTOP=Unity
GTK_IM_MODULE=ibus
LESSCLOSE=/usr/bin/lesspipe %s %s
XAUTHORITY=/home/julien/.Xauthority
OLDPWD=/home/julien/c
_=/usr/bin/printenv
julien@ubuntu:~/c/shell$
```
Actually, every process comes with an environment. When a new process is created, it inherits a copy of its parent’s environment. To access the entire environment within a process, you have several options:
* via the `main` function
* via the global variable `environ` (man environ)

## main
So far we have seen that `main` could have different prototypes:
* `int main(void);`
* `int main(int ac, char **av);`

There is actually another prototype:
* `int main(int ac, char **av, char **env);`

where `env` is a `NULL` terminated array of strings.
```
julien@ubuntu:~/c/shell$ cat env-main.c
#include <stdio.h>

/**
 * main - prints the environment
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
    unsigned int i;

    i = 0;
    while (env[i] != NULL)
    {
        printf("%s\n", env[i]);
        i++;
    }
    return (0);
}
julien@ubuntu:~/c/shell$ gcc -Wall -Werror -pedantic env-main.c -o printenv && ./printenv 
XDG_VTNR=7
XDG_SESSION_ID=c2
CLUTTER_IM_MODULE=xim
XDG_GREETER_DATA_DIR=/var/lib/lightdm-data/julien
SESSION=ubuntu
GPG_AGENT_INFO=/home/julien/.gnupg/S.gpg-agent:0:1
TERM=xterm-256color
SHELL=/bin/bash
XDG_MENU_PREFIX=gnome-
VTE_VERSION=4205
QT_LINUX_ACCESSIBILITY_ALWAYS_ON=1
WINDOWID=23068682
UPSTART_SESSION=unix:abstract=/com/ubuntu/upstart-session/1000/1558
GNOME_KEYRING_CONTROL=
GTK_MODULES=gail:atk-bridge:unity-gtk-module
USER=julien
LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=30;41:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.Z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.jpg=01;35:*.jpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:
QT_ACCESSIBILITY=1
XDG_SESSION_PATH=/org/freedesktop/DisplayManager/Session0
XDG_SEAT_PATH=/org/freedesktop/DisplayManager/Seat0
SSH_AUTH_SOCK=/run/user/1000/keyring/ssh
SESSION_MANAGER=local/ubuntu:@/tmp/.ICE-unix/1792,unix/ubuntu:/tmp/.ICE-unix/1792
DEFAULTS_PATH=/usr/share/gconf/ubuntu.default.path
XDG_CONFIG_DIRS=/etc/xdg/xdg-ubuntu:/usr/share/upstart/xdg:/etc/xdg
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DESKTOP_SESSION=ubuntu
QT_IM_MODULE=ibus
QT_QPA_PLATFORMTHEME=appmenu-qt5
XDG_SESSION_TYPE=x11
JOB=dbus
PWD=/home/julien/c/shell
XMODIFIERS=@im=ibus
GNOME_KEYRING_PID=
LANG=en_US.UTF-8
GDM_LANG=en_US
MANDATORY_PATH=/usr/share/gconf/ubuntu.mandatory.path
IM_CONFIG_PHASE=1
COMPIZ_CONFIG_PROFILE=ubuntu
GDMSESSION=ubuntu
SESSIONTYPE=gnome-session
GTK2_MODULES=overlay-scrollbar
XDG_SEAT=seat0
HOME=/home/julien
SHLVL=1
LANGUAGE=en_US
GNOME_DESKTOP_SESSION_ID=this-is-deprecated
XDG_SESSION_DESKTOP=ubuntu
LOGNAME=julien
QT4_IM_MODULE=xim
XDG_DATA_DIRS=/usr/share/ubuntu:/usr/share/gnome:/usr/local/share/:/usr/share/:/var/lib/snapd/desktop
DBUS_SESSION_BUS_ADDRESS=unix:abstract=/tmp/dbus-jH9kfagEpM
LESSOPEN=| /usr/bin/lesspipe %s
INSTANCE=
XDG_RUNTIME_DIR=/run/user/1000
DISPLAY=:0
XDG_CURRENT_DESKTOP=Unity
GTK_IM_MODULE=ibus
LESSCLOSE=/usr/bin/lesspipe %s %s
XAUTHORITY=/home/julien/.Xauthority
OLDPWD=/home/julien/c
_=./printenv
julien@ubuntu:~/c/shell$
```
## Exercises
#### 0. printenv with environ
Write a program that prints the environment using the global variable `environ`.

#### 1. env vs environ
Write a program that prints the address of `env` (the third parameter of the `main` function) and `environ` (the global variable). Are they they same? Does this make sense?

#### 2. getenv()
Write a function that gets an environment variable. (without using getenv)
* Prototype: `char *_getenv(const char *name);`

man 3 `getenv`

#### 3. PATH
Write a function that prints each directory contained in the the environment variable `PATH`, one directory per line.

#### 4. PATH
Write a function that builds a linked list of the `PATH` directories.

#### 5. setenv
Write a function that changes or adds an environment variable (without using `setenv`).
* Prototype: `int _setenv(const char *name, const char *value, int overwrite);`

man 3 `setenv`

#### 6. unsetenv
Write a function that deletes the variable name from the environment (without using `unsetenv`).
* Prototype: `int _unsetenv(const char *name);`

man 3 `unsetenv`

# 2. Approaching a Project
It can be difficult to know how to approach a project. You’ve read resources and tried some examples, and now it’s time to apply what you know. Where do you start? The following framework can help you focus how you approach a project.

Read the steps below and think about how you would follow them for a task.
1. Read the task or challenge.
2. Rephrase it in your own words.
3. Verify expected behavior by getting example inputs and outputs.
4. Whiteboard your solution with words.
5. Walk through your solution with an example as if you were a machine. Do only what is written down. Correct your solution if needed.
6. Whiteboard your solution with pseudocode.
7. Walk through your solution with an example as if you were a machine. Do only what is written down. Correct your solution if needed.
8. Whiteboard your solution with code.
9. Walk through your solution with an example as if you were a machine. Do only what is written down. Correct your solution if needed.
10. Write your code on your computer. _[Note: This is this first time you are using your computer! Only when you know **exactly** what to code.]_
11. Test your code on your computer.
12. Debug if necessary.
13. You complete the task or challenge!

Be sure to break your task or project into smaller and smaller pieces, until you are comfortable solving each piece with the above steps.

When you are in step 10, “Write your code on your computer”, you should code each piece one at a time and debug right after each small step to make sure everything works properly. This will also prevent you from having to debug multiple pieces at the same time and thus, will make your life much easier.

# Background Context
Write a simple UNIX command interpreter.

![shell](https://github.com/elyse502/simple_shell/assets/125453474/a4dd7759-11dc-4cff-a9f9-bd988d1bb4de)

_^ “The Gates of Shell”, by [Spencer Cheng](https://twitter.com/spencerhcheng/status/855104635069054977), featuring [Julien Barbier](https://twitter.com/julienbarbier42)_

# Resources🏗️
## Read or watch:
* [Unix shell](https://en.wikipedia.org/wiki/Unix_shell)
* [Thompson shell](https://en.wikipedia.org/wiki/Thompson_shell)
* [Ken Thompson](https://en.wikipedia.org/wiki/Ken_Thompson)
* **Everything you need to know to start coding your own shell** concept page

### man or help:
* `sh` (_Run `sh` as well_)

# General
* Who designed and implemented the original Unix operating system
* Who wrote the first version of the UNIX shell
* Who invented the B programming language (the direct predecessor to the C programming language)
* Who is Ken Thompson
* How does a shell work
* What is a pid and a ppid
* How to manipulate the environment of the current process
* What is the difference between a function and a system call
* How to create processes
* What are the three prototypes of `main`
* How does the shell use the `PATH` to find the programs
* How to execute another program with the `execve` system call
* How to suspend the execution of a process until one of its children terminates
* What is `EOF` / “end-of-file”?

# More Info
## Output
* Unless specified otherwise, your program **must have the exact same output** as `sh` (`/bin/sh`) as well as the exact same error output.
* The only difference is when you print an error, the name of the program must be equivalent to your `argv[0]` (See below)

Example of error with `sh`:
```
$ echo "qwerty" | /bin/sh
/bin/sh: 1: qwerty: not found
$ echo "qwerty" | /bin/../bin/sh
/bin/../bin/sh: 1: qwerty: not found
$
```
Same error with your program `hsh`:
```
$ echo "qwerty" | ./hsh
./hsh: 1: qwerty: not found
$ echo "qwerty" | ./././hsh
./././hsh: 1: qwerty: not found
$
```

## List of allowed functions and system calls
* `access` (man 2 access)
* `chdir` (man 2 chdir)
* `close` (man 2 close)
* `closedir` (man 3 closedir)
* `execve` (man 2 execve)
* `exit` (man 3 exit)
* `_exit` (man 2 _exit)
* `fflush` (man 3 fflush)
* `fork` (man 2 fork)
* `free` (man 3 free)
* `getcwd` (man 3 getcwd)
* `getline` (man 3 getline)
* `getpid` (man 2 getpid)
* `isatty` (man 3 isatty)
* `kill` (man 2 kill)
* `malloc` (man 3 malloc)
* `open` (man 2 open)
* `opendir` (man 3 opendir)
* `perror` (man 3 perror)
* `read` (man 2 read)
* `readdir` (man 3 readdir)
* `signal` (man 2 signal)
* `stat` (__xstat) (man 2 stat)
* `lstat` (__lxstat) (man 2 lstat)
* `fstat` (__fxstat) (man 2 fstat)
* `strtok` (man 3 strtok)
* `wait` (man 2 wait)
* `waitpid` (man 2 waitpid)
* `wait3` (man 2 wait3)
* `wait4` (man 2 wait4)
* `write` (man 2 write)

## Compilation
Your shell will be compiled this way:
```
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 *.c -o hsh
```
## Testing
Your shell should work like this in interactive mode:
```
$ ./hsh
($) /bin/ls
hsh main.c shell.c
($)
($) exit
$
```
But also in non-interactive mode:
```
$ echo "/bin/ls" | ./hsh
hsh main.c shell.c test_ls_2
$
$ cat test_ls_2
/bin/ls
/bin/ls
$
$ cat test_ls_2 | ./hsh
hsh main.c shell.c test_ls_2
hsh main.c shell.c test_ls_2
$
```
## Checks
The Checker will be released at the end of the project (1-2 days before the deadline). We **strongly** encourage the entire class to work together to create a suite of checks covering both regular tests and edge cases for each task. See task `8. Test suite`.

# Tasks📃
## 0. Betty would be proud: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Write a beautiful code that passes the Betty checks

## 1. Simple shell 0.1: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Write a UNIX command line interpreter.
* Usage: `simple_shell`

Your Shell should:
* Display a prompt and wait for the user to type a command. A command line always ends with a new line.
* The prompt is displayed again each time a command has been executed.
* The command lines are simple, no semicolons, no pipes, no redirections or any other advanced features.
* The command lines are made only of one word. No arguments will be passed to programs.
* If an executable cannot be found, print an error message and display the prompt again.
* Handle errors.
* You have to handle the “end of file” condition (`Ctrl+D`)

You don’t have to:
* use the `PATH`
* implement built-ins
* handle special characters : `"`, `'`, `'`, `\`, `*`, `&`, `#`
* be able to move the cursor
* handle commands with arguments

_`execve` will be the core part of your Shell, don’t forget to pass the environ to it…_
```
julien@ubuntu:~/shell$ ./shell 
#cisfun$ ls
./shell: No such file or directory
#cisfun$ /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ /bin/ls -l
./shell: No such file or directory
#cisfun$ ^[[D^[[D^[[D
./shell: No such file or directory
#cisfun$ ^[[C^[[C^[[C^[[C
./shell: No such file or directory
#cisfun$ exit
./shell: No such file or directory
#cisfun$ ^C
julien@ubuntu:~/shell$ echo "/bin/ls" | ./shell
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell.c  stat.c         wait
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     stat test_scripting.sh  wait.c
#cisfun$ julien@ubuntu:~/shell$
```
## 2. Simple shell 0.2: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.1 +
* Handle command lines with arguments

## 3. Simple shell 0.3: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.2 +
* Handle the `PATH`
* `fork` must not be called if the command doesn’t exist
```
julien@ubuntu:~/shell$ ./shell_0.3
:) /bin/ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls
barbie_j       env-main.c  exec.c  fork.c  pid.c  ppid.c    prompt   prompt.c  shell_0.3  stat    test_scripting.sh  wait.c
env-environ.c  exec    fork    mypid   ppid   printenv  promptc  shell     shell.c    stat.c  wait
:) ls -l /tmp 
total 20
-rw------- 1 julien julien    0 Dec  5 12:09 config-err-aAMZrR
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-colord.service-V7DUzr
drwx------ 3 root   root   4096 Dec  5 12:09 systemd-private-062a0eca7f2a44349733e78cb4abdff4-rtkit-daemon.service-ANGvoV
drwx------ 3 root   root   4096 Dec  5 12:07 systemd-private-062a0eca7f2a44349733e78cb4abdff4-systemd-timesyncd.service-CdXUtH
-rw-rw-r-- 1 julien julien    0 Dec  5 12:09 unity_support_test.0
:) ^C
julien@ubuntu:~/shell$ 
```
## 4. Simple shell 0.4: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.3 +
* Implement the `exit` built-in, that exits the shell
* Usage: `exit`
* You don’t have to handle any argument to the built-in `exit`

## 5. Simple shell 1.0: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.4 +
* Implement the `env` **built-in**, that prints the current environment
```
julien@ubuntu:~/shell$ ./simple_shell
$ env
USER=julien
LANGUAGE=en_US
SESSION=ubuntu
COMPIZ_CONFIG_PROFILE=ubuntu
SHLVL=1
HOME=/home/julien
C_IS=Fun_:)
DESKTOP_SESSION=ubuntu
LOGNAME=julien
TERM=xterm-256color
PATH=/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
DISPLAY=:0
$ exit
julien@ubuntu:~/shell$ 
```
## 6. Simple shell 0.1.1: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.1 +
* Write your own `getline` function
* Use a buffer to read many chars at once and call the least possible the `read` system call
* You will need to use `static` variables
* You are not allowed to use `getline`

You don’t have to:
* be able to move the cursor

## 7. Simple shell 0.2.1: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.2 +
* You are not allowed to use `strtok`

## 8. Simple shell 0.4.1: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 0.4 +
* handle arguments for the built-in exit
* Usage: exit status, where status is an integer used to exit the shell
```
julien@ubuntu:~/shell$ ./shell_0.4.1
$ exit 98
julien@ubuntu:~/shell$ echo $?
98
julien@ubuntu:~/shell$
```
## 9. setenv, unsetenv: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +

Implement the `setenv` and `unsetenv` builtin commands

* `setenv`
    * Initialize a new environment variable, or modify an existing one
    * Command syntax: `setenv VARIABLE VALUE`
    * Should print something on stderr on failure
* `unsetenv`
    * Remove an environment variable
    * Command syntax: `unsetenv VARIABLE`
    * Should print something on stderr on failure

## 10. cd: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +

Implement the builtin command `cd`:
* Changes the current directory of the process.
* Command syntax: `cd [DIRECTORY]`
* If no argument is given to `cd` the command must be interpreted like `cd $HOME`
* You have to handle the command `cd -`
* You have to update the environment variable `PWD` when you change directory

`man chdir`, `man getcwd`

## 11. ;: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +
* Handle the commands separator `;`
```
alex@~$ ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn ; ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /var ; ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var ; ls /hbtn ; ls /var ; ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$
```
## 12. && and ||: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +
* Handle the `&&` and `||` shell logical operators
```
alex@~$ ls /var && ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn && ls /var
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var && ls /var && ls /var && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$ ls /var && ls /var && ls /var && ls /hbtn && ls /hbtn
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
ls: cannot access /hbtn: No such file or directory
alex@~$
alex@~$ ls /var || ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$ ls /hbtn || ls /hbtn || ls /hbtn || ls /var || ls /var
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
ls: cannot access /hbtn: No such file or directory
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  spool  tmp
alex@~$
```
## 13. alias: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +
* Implement the `alias` builtin command
* Usage: `alias [name[='value'] ...]`
    * `alias`: Prints a list of all aliases, one per line, in the form `name='value'`
    * `alias name [name2 ...]`: Prints the aliases `name`, `name2`, etc 1 per line, in the form `name='value'`
    * `alias name='value' [...]`: Defines an alias for each `name` whose `value` is given. If `name` is already an alias, replaces its value with `value`

## 14. Variables: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +
* Handle variables replacement
* Handle the `$?` variable
* Handle the `$$` variable
```
julien@ubuntu:~/shell$ ./hsh
$ ls /var
backups  cache  crash  lib  local  lock  log  mail  metrics  opt  run  snap  spool  tmp
$ echo $?
0
$ echo $$
5104
$ echo $PATH
/home/julien/bin:/home/julien/.local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
$ exit 
julien@ubuntu:~/shell$ 
```
## 15. Comments: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +
* Handle comments (`#`)
```
julien@ubuntu:~/shell$ sh
$ echo $$ # ls -la
5114
$ exit
julien@ubuntu:~/shell$
``` 
## 16. File as input: [simple_shell](https://github.com/elyse502/simple_shell/tree/master)
Simple shell 1.0 +
* Usage: `simple_shell [filename]`
* Your shell can take a file as a command line argument
* The file contains all the commands that your shell should run before exiting
* The file should contain one command per line
* In this mode, the shell should not print a prompt and should not read from `stdin`







