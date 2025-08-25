Custom Command-Line Interface (CLI) in C
📌 Overview

This project is a console-based shell/command language interface implemented in C, designed to simulate basic file and disk management operations similar to Windows CMD, Linux shell, or Mac Terminal.

It continuously accepts user input and executes commands, allowing users to practice process creation, file descriptors, and system calls in C while providing essential file management features.

🎯 Objectives

Gain hands-on experience with advanced C programming techniques such as process creation and control.

Build a working shell that supports navigation commands, directory listing, and file operations.

Strengthen programming dexterity in C (a critical skill for technical interviews and job applications).

⚙️ Features / Supported Commands

The shell supports the following commands:

dir → Lists files and directories in the current directory.

cd <directory> → Changes the current working directory.

cd.. → Moves to the parent directory.

mkdir <directory> → Creates a new directory.

rmdir <directory> → Removes an empty directory.

del <file> → Deletes a file in the current directory.

touch <file> → Creates an empty text file.

type <file> → Displays the contents of a file.

help → Lists all available commands with brief descriptions.

cls → Clears the screen.

date → Displays or updates the system date.

time → Displays or updates the system time.

exit → Terminates the shell.

The program also handles erroneous inputs gracefully, continuously prompting until a valid command is entered.

🚀 How to Run

Clone this repository:

git clone https://github.com/your-username/your-repo-name.git


Navigate to the project folder:

cd your-repo-name


Compile the program:

gcc shell.c -o shell


Run the shell:

./shell

🖥️ Sample Usage
> dir
file1.txt   project.c   docs/

> cd docs
> mkdir reports
> cd..
> touch notes.txt
> type notes.txt
# (prints file contents)

> help
# (shows list of commands)

> exit

📚 Notes

The implementation assumes text files only for touch and type.

Behavior is modeled after Windows CMD and Unix-like shells, but simplified.

This project is for educational purposes and demonstrates the fundamentals of building a shell in C.
