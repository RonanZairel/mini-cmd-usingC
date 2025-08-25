# 🖥️ Custom Command-Line Interface (CLI) in C

## 📌 Overview
This project is a **console-based shell/command language interface** implemented in **C**, designed to simulate basic file and disk management operations similar to **Windows CMD**, **Linux shell**, or **Mac Terminal**.  

It continuously accepts user input and executes commands, allowing users to practice **process creation**, **file descriptors**, and **system calls** in C while providing essential file management features.

---

## 🎯 Objectives
- Gain hands-on experience with advanced C programming techniques such as **process creation and control**.  
- Build a working shell that supports **navigation commands, directory listing, and file operations**.  
- Strengthen programming dexterity in C (a critical skill for technical interviews and job applications).  

---

## ⚙️ Features / Supported Commands
The shell supports the following commands:

- **`dir`** → Lists files and directories in the current directory.  
- **`cd <directory>`** → Changes the current working directory.  
- **`cd..`** → Moves to the parent directory.  
- **`mkdir <directory>`** → Creates a new directory.  
- **`rmdir <directory>`** → Removes an empty directory.  
- **`del <file>`** → Deletes a file in the current directory.  
- **`touch <file>`** → Creates an empty text file.  
- **`type <file>`** → Displays the contents of a file.  
- **`help`** → Lists all available commands with brief descriptions.  
- **`cls`** → Clears the screen.  
- **`date`** → Displays or updates the system date.  
- **`time`** → Displays or updates the system time.  
- **`exit`** → Terminates the shell.  

The program also **handles erroneous inputs gracefully**, continuously prompting until a valid command is entered.  

---

## 🚀 How to Run
1. Clone this repository:
   ```bash
   git clone https://github.com/RonanZairel/mini-cmd-usingC.git
2. Navigate to the project folder:
   cd mini-cmd-usingC

3. Compile the program:
  gcc minicmd.c -o minicmd
   
4. Run the shell:
   ./minicmd.exe  
