#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <direct.h>
#include <direct.h>
#include <shlobj.h>

#define MAX_INPUT 1024
#define MAX_ARGS 64


void parse_input(char *input, char **args) {
    int i = 0;
    char *token = strtok(input, " \t\n");
    while (token != NULL && i < MAX_ARGS - 1) {
        args[i++] = token;
        token = strtok(NULL, " \t\n");
    }
    args[i] = NULL;
}

void handle_dir(char **args) {
    char command[MAX_PATH * 2];

    if (args[1] != NULL) {
        // If a path or argument is provided, include it in the dir command
        snprintf(command, sizeof(command), "cmd /c dir \"%s\"", args[1]);
    } else {
        // No argument provided, use current directory
        char cwd[MAX_PATH];
        if (GetCurrentDirectory(MAX_PATH, cwd)) {
            snprintf(command, sizeof(command), "cmd /c dir \"%s\"", cwd);
        } else {
            perror("getcwd error");
            return;
        }
    }

    system(command);
}

void handle_type(char **args) {
    if (args[1] == NULL) {
        printf("Usage: type <filename>\n");
        return;
    }

    FILE *file = fopen(args[1], "r");
    if (file == NULL) {
        printf("The system cannot find the file specified.\n");
        return;
    }

    char ch;
    while ((ch = fgetc(file)) != EOF) {
        putchar(ch);
    }

    fclose(file);
}

void handle_cls() {
    system("cls");
}

void handle_date(char **args) {
    time_t t;
    struct tm new_time;
    char date_input[20];

    // Get and show current date
    time(&t);
    struct tm *tm_info = localtime(&t);
    printf("Current date: %02d-%02d-%04d\n", 
           tm_info->tm_mon + 1, tm_info->tm_mday, tm_info->tm_year + 1900);

    // Ask user for new date and keep prompting until valid input
    while (1) {
        printf("Enter the new date: (mm-dd-yy)\n");
        fgets(date_input, sizeof(date_input), stdin);

        // Remove trailing newline
        date_input[strcspn(date_input, "\n")] = '\0';

        // If input is empty, skip setting
        if (strlen(date_input) == 0) {
            printf("Date unchanged.\n");
            return;
        }

        // Parse input
        int month, day, year;
        if (sscanf(date_input, "%2d-%2d-%2d", &month, &day, &year) == 3) {
            // Expand 2-digit year correctly
            int full_year = (year < 50) ? (2000 + year) : (1900 + year);
    
            new_time.tm_mon = month - 1;
            new_time.tm_mday = day;
            new_time.tm_year = full_year - 1900;
            new_time.tm_hour = 0;
            new_time.tm_min = 0;
            new_time.tm_sec = 0;
            new_time.tm_isdst = -1;
    
            SYSTEMTIME system_time;
            system_time.wYear = full_year;
            system_time.wMonth = month;
            system_time.wDay = day;
            system_time.wHour = 0;
            system_time.wMinute = 0;
            system_time.wSecond = 0;
            system_time.wMilliseconds = 0;
    
            // Check if the input date is valid (this check should not be skipped)
            if (new_time.tm_mon >= 0 && new_time.tm_mon <= 11 && new_time.tm_mday > 0 && new_time.tm_mday <= 31) {
                if (SetSystemTime(&system_time)) {
                    printf("Date updated successfully to: %02d-%02d-%04d\n", 
                           month, day, full_year);
                    return;
                } else {
                    printf("The system cannot accept the date entered.\n");
                }
            } else {
                printf("The system cannot accept the date entered.\n");
            }
        } else {
            printf("The system cannot accept the date entered.\n");
        }
    }
}

void handle_time(char **args) {
    SYSTEMTIME current_time;
    GetLocalTime(&current_time);  // Use local time

    printf("The current time is: %02d:%02d:%02d.%03d\n", 
           current_time.wHour, current_time.wMinute, current_time.wSecond, current_time.wMilliseconds);

    char time_input[20];
    int hour, minute, second;

    while (1) {
        printf("Enter the new time: ");
        fgets(time_input, sizeof(time_input), stdin);
        time_input[strcspn(time_input, "\n")] = '\0';

        if (strlen(time_input) == 0) {
            printf("Time unchanged.\n");
            return;
        }

        if (sscanf(time_input, "%2d:%2d:%2d", &hour, &minute, &second) == 3 &&
            hour >= 0 && hour <= 23 && minute >= 0 && minute <= 59 && second >= 0 && second <= 59) {

            SYSTEMTIME local_time, utc_time;
            GetLocalTime(&local_time);

            local_time.wHour = hour;
            local_time.wMinute = minute;
            local_time.wSecond = second;
            local_time.wMilliseconds = 0;

            // Convert from local time to UTC
            if (!TzSpecificLocalTimeToSystemTime(NULL, &local_time, &utc_time)) {
                printf("The system cannot accept the time entered.\n");
                continue;
            }

            if (SetSystemTime(&utc_time)) {
                printf("Time updated successfully to: %02d:%02d:%02d\n", hour, minute, second);
            } else {
                printf("The system cannot accept the time entered.\n");
            }
            return;
        } else {
            printf("The system cannot accept the time entered.\n");
        }
    }
}

void handle_touch(char **args) {
    if (args[1] == NULL) {
        printf("Usage: touch <filename>\n");
        return;
    }

    // Check if the file already exists
    FILE *file = fopen(args[1], "r");
    if (file != NULL) {
        printf("File already exists: %s\n", args[1]);
        fclose(file);
        return;
    }

    // Create the file
    file = fopen(args[1], "w");
    if (file == NULL) {
        printf("Error: Could not create the file %s\n", args[1]);
        return;
    }

    printf("File created successfully: %s\n", args[1]);
    fclose(file);
}

void handle_del(char **args) {
    if (args[1] == NULL) {
        printf("Usage: del <filename>\n");
        return;
    }

    // Attempt to delete the file
    if (remove(args[1]) == 0) {
        printf("File deleted successfully: %s\n", args[1]);
    } else {
        printf("Error: Could not delete the file %s. It may not exist.\n", args[1]);
    }
}

void handle_mkdir(char **args) {
    if (args[1] == NULL) {
        printf("Usage: mkdir <directory>\n");
        return;
    }

    // Attempt to create the directory
    if (_mkdir(args[1]) == 0) {
        printf("Directory created successfully: %s\n", args[1]);
    } else {
        printf("Error: Could not create the directory %s. It may already exist.\n", args[1]);
    }
}

void handle_rmdir(char **args) {
    if (args[1] == NULL) {
        printf("Usage: rmdir <directory>\n");
        return;
    }

    // Attempt to remove the directory
    if (_rmdir(args[1]) == 0) {
        printf("Directory removed successfully: %s\n", args[1]);
    } else {
        printf("The system cannot find the file specified.\n", args[1]);
    }
}

void handle_cdhome();
void handle_cd(char **args) {
    if (args[1] == NULL) {
        // If no argument is given, print current directory
        char cwd[MAX_PATH];
        if (GetCurrentDirectory(MAX_PATH, cwd)) {
            printf("%s\n", cwd);
        } else {
            perror("getcwd error");
        }
        return;
    }

    // Handle special case: cd ..
    if (strcmp(args[1], "..") == 0) {
        handle_cdhome();  // Go to mother directory
        return;
    }

    char target[MAX_PATH];

    // If the path is relative (like "Desktop" or "Downloads")
    if (strchr(args[1], ':') == NULL && args[1][0] != '\\') {
        // Get home directory (e.g., C:\Users\ADMIN)
        char home[MAX_PATH];
        SHGetFolderPath(NULL, CSIDL_PROFILE, NULL, 0, home);

        snprintf(target, MAX_PATH, "%s\\%s", home, args[1]);
    } else {
        // Absolute path (like "C:\SomeFolder")
        strncpy(target, args[1], MAX_PATH);
    }

    if (_chdir(target) != 0) {
        perror("The system cannot find the path specified.");
    }
}

void handle_help() {
    printf("List of available commands:\n");
    printf("dir                 : Lists all files and directories in the current directory.\n");
    printf("cd <directory>      : Change the current working directory.\n");
    printf("cd ..               : Move to the parent directory.\n");
    printf("mkdir <directory>   : Create a new directory.\n");
    printf("rmdir <directory>   : Remove an empty directory.\n");
    printf("del <file>          : Delete a specified file.\n");
    printf("touch <file>        : Create a file in the current directory.\n");
    printf("type <file>         : Display the content of a specified file.\n");
    printf("help                : List all available commands.\n");
    printf("cls                 : Clear the screen.\n");
    printf("date                : Display and update the system date.\n");
    printf("time                : Display and update the system time.\n");
    printf("exit                : Exit the command-line interface.\n");
}

void handle_cdhome() {
    if (_chdir("C:\\Users\\ADMIN\\CMSC125Lab4") != 0) {
        perror("cdhome error");
    }
}

int main() {
    char input[MAX_INPUT];
    char *args[MAX_ARGS];
    char cwd[MAX_PATH];

    printf("Command Propmt\n");

    // Set the "mother directory"
    _chdir("C:\\Users\\ADMIN\\CMSC125Lab4");

    while (1) {
        // Get current working directory for prompt
        if (_getcwd(cwd, sizeof(cwd)) != NULL) {
            printf("%s> ", cwd);
        } else {
            perror("getcwd error");
            break;
        }

        if (!fgets(input, MAX_INPUT, stdin)) break;

        parse_input(input, args);
        if (args[0] == NULL) continue;

        if (strcmp(args[0], "exit") == 0) {
            break;
        } else if (strcmp(args[0], "dir") == 0) {
                handle_dir(args);
        } else if (strcmp(args[0], "date") == 0) {
            handle_date(args);
        } else if (strcmp(args[0], "time") == 0) {
            handle_time(args);
        } else if (strcmp(args[0], "help") == 0) {
            handle_help();
        } else if (strcmp(args[0], "cd") == 0) {
            handle_cd(args);
        } else if (strcmp(args[0], "cls") == 0) {
            handle_cls();
        } else if (strcmp(args[0], "type") == 0) {
            handle_type(args);
        } else if (strcmp(args[0], "touch") == 0) {
            handle_touch(args);
        } else if (strcmp(args[0], "del") == 0) {
            handle_del(args);
        } else if (strcmp(args[0], "rmdir") == 0) {
            handle_rmdir(args);
        } else if (strcmp(args[0], "mkdir") == 0) {
            handle_mkdir(args);
        } else if (strcmp(args[0], "cdhome") == 0) {
            handle_cdhome();
        } else {
            printf("Unknown command: %s\n", args[0]);
        }
    }

    return 0;
}