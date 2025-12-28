# Simple Shell

A lightweight Unix shell implementation in C featuring process management, command parsing, and built-in commands.

## Features

- Custom command prompt showing current directory
- Process forking and execution using `fork()` and `execvp()`
- Built-in commands: `cd`, `exit`
- External command execution (ls, cat, grep, etc.)
- Clean error handling

## Build

```bash
gcc shell.c -o shell
```

## Usage

```bash
./shell

# Example session:
/home/user> ls
file1.txt  file2.txt  folder/

/home/user> cd folder
/home/user/folder> pwd
/home/user/folder

/home/user/folder> exit
Shell exiting...
```

## Technical Details

**System Calls Used:**
- `fork()` - Create child processes
- `execvp()` - Execute commands
- `wait()` - Wait for child process completion
- `chdir()` - Change directory
- `getcwd()` - Get current working directory

**Key Concepts:**
- Process management
- String parsing and tokenization
- Parent-child process communication

## Future Enhancements

- [ ] Pipe support (`|`)
- [ ] Redirection (`>`, `<`, `>>`)
- [ ] Background processes (`&`)
- [ ] Command history
- [ ] Tab completion
- [ ] AI agent integration for command suggestions

## License

Educational project for systems programming coursework.
