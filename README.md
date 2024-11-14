Minishell:

Minishell is a simple command-line shell that emulates the functionality of Bash.
Written in C, this project aims to replicate fundamental shell behaviors, including 
handling environment variables, input/output redirections, command execution, and other shell built-ins.

Features
Execution of Commands: Runs external commands and built-in shell commands (cd, echo, export, unset, etc.).

Environment Variables: Supports the usage of environment variables, including expansion within commands.

Error Handling: Provides informative error messages, similar to Bash, and handles invalid command sequences.

Redirection: Implements input/output redirection (>, >>, <) and piping (|).

Exit Status: Tracks and displays exit statuses for commands, like a real shell.

Signal Handling: Gracefully handles signals (e.g., Ctrl+C, Ctrl+D) to simulate Bash-like behavior.

Quoting: Manages quoted arguments and prevents interpretation of special characters within quotes.

Requirements
Language: C
System: Unix-based OS (e.g., Linux or macOS)
Compiler: gcc

Installation
Clone the Repository:
bash
Copy code
git clone https://github.com/username/minishell.git
cd minishell

Compile the Project:
bash
Copy code
make
This will generate an executable named minishell.

Usage
Start minishell by running the executable:

bash
Copy code
./minishell
In minishell, you can execute commands as you would in Bash. Here are a few examples:

Basic Commands:
bash
  ls -l
  echo "Hello, Minishell!"

Environment Variable Expansion:
  echo $USER

Redirections:
  echo "Log this" > logfile.txt
  cat < logfile.txt

Piping:
  ls -l | grep minishell

Type exit to quit the shell.

Project Structure
src/: Contains all source code files (*.c).
includes/: Header files used across the project.
Makefile: Automates the build process.
README.md: Project documentation.

Limitations
While minishell replicates many Bash features, some complex shell behaviors are not fully supported:

It does not handle advanced shell scripting or complex pipes/redirection combinations.
Lack of support for job control (e.g., bg, fg commands).
No support for wildcards (*) and other complex pattern matching.

Future Improvements:

Add job control features.

Improve memory management and efficiency.

Extend support for more complex Bash features and syntaxes.

Authors
Vikas Sharma - Parsing and signal handeling

Rene Scherl  - Excution and Redirection handeling
