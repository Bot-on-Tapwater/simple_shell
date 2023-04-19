# Simple Shell Project
This is a simple shell project written in C. It allows users to execute basic commands such as cd, ls, pwd, echo, and many more.

## How to Use
To run the program, compile the code using the following command:

`gcc -o shell shell.c`

Then, run the executable by typing the following command:

`./shell`

The shell will then start, and you can enter commands just like you would in a regular terminal.

## Supported Commands
The following commands are supported by the shell:

- cd - change directory
- ls - list directory contents
- pwd - print working directory
- echo - print text to the console
- mkdir - create a new directory
- rmdir - remove a directory
- rm - remove a file
- cp - copy a file
- mv - move a file
- chmod - change file permissions
- exit - exit the shell

## Limitations
This shell has some limitations that you should be aware of:

- The shell cannot execute complex commands such as those involving pipes (|) or redirects (> and <).
- The shell does not support wildcard expansion (e.g. ls *.txt).
- The shell does not provide any autocomplete functionality.

## Credits
This project was created by ***Brandon Munda*** && ***Winfred Ngina***.

Feel free to fork and improve the project as needed!