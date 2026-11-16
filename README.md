# Minishell 2

> **Unix command shell with pipes and file redirections.**

## Overview
Expands upon Minishell 1 by adding full inter-process communication pipelines and file descriptors management:
- Pipelines: command piping (`cmd1 | cmd2 | cmd3`) using `pipe` and `dup2`
- Redirections: input redirection (`<`), heredoc (`<<`), output redirection (`>`), append output (`>>`)
- Command separators (`;`)

## Build & Usage
```bash
make
./mysh
```

## License
Open-source under MIT License.
