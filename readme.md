# MiniShell

> A minimal Unix shell built from scratch in C, replicating core Bash behavior.

![C](https://img.shields.io/badge/C-99-blue.svg)
![Linux](https://img.shields.io/badge/Linux-Unix-green.svg)
![Team](https://img.shields.io/badge/Team-2_devs-orange.svg)

---

## ✨ Features

### Builtins
| Command | Description |
|---|---|
| `cd` | Change current directory |
| `echo` | Print arguments to stdout |
| `env` | Display environment variables |
| `export` | Set environment variables |
| `unset` | Remove environment variables |
| `exit` | Exit the shell with status code |
| `pwd` | Print current working directory |

### Shell Mechanics
- **Pipes** `|` — chain commands, connecting stdout to stdin
- **Redirections** — `>` (output), `>>` (append), `<` (input), `<<` (heredoc)
- **Heredoc** `<<` — read input until delimiter is reached
- **Environment variables** — `$VAR` expansion
- **Exit status** — `$?` reflects last command return code
- **Signal handling** — `Ctrl+C`, `Ctrl+D`, `Ctrl+\` behave like Bash

---

## 🛠️ Build & Run

### Requirements
- Linux / macOS
- `gcc` or `clang`
- `make`
- `readline` library

### Build
```bash
git clone https://github.com/Elyesthe1/minishell.git
cd minishell
make
```

### Run
```bash
./minishell
```

---

## 💻 Usage Examples

```bash
# Pipes
ls -la | grep .c | wc -l

# Redirections
echo "hello" > file.txt
cat < file.txt >> output.txt

# Heredoc
cat << EOF
line1
line2
EOF

# Environment variables
export NAME=Elyes
echo $NAME
echo $?

# Chained commands
cd /tmp && ls -la | grep log > results.txt
```

---

## 🏗️ Architecture

```
┌─────────────────────────────────────────┐
│              MiniShell Loop             │
│                                         │
│  ┌──────────┐    ┌────────────────────┐ │
│  │  Lexer   │───▶│      Parser        │ │
│  │(tokenize)│    │    (cmd list)      │ │
│  └──────────┘    └────────┬───────────┘ │
│                           │             │
│                  ┌────────▼───────────┐ │
│                  │     Executor       │ │
│                  │  - fork / execve   │ │
│                  │  - pipe chaining   │ │
│                  │  - redirections    │ │
│                  │  - builtins        │ │
│                  └────────────────────┘ │
└─────────────────────────────────────────┘
```

---

## 🔧 Key System Calls

| Call | Usage |
|---|---|
| `fork` | Create child process |
| `execve` | Execute external commands |
| `pipe` | Connect processes via file descriptors |
| `dup2` | Redirect file descriptors |
| `wait / waitpid` | Collect child exit status |
| `access` | Check command existence in PATH |
| `readline` | Interactive input with history |

---

## 👥 Team

Built by 2 students at [42 Nice](https://42nice.fr) using Agile methodology and Git workflow.

---

## 📄 License

This project was developed as part of the 42 curriculum.
