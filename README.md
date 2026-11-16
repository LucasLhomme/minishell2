# 🐚 Minishell 2 — Unix Shell with Pipelines & Redirections

[![Language: C](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build: Make](https://img.shields.io/badge/Build-Makefile-orange.svg)](Makefile)
[![Module: B-PSU-200](https://img.shields.io/badge/Epitech-B--PSU--200-blue.svg)](https://www.epitech.eu/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)

> **Minishell 2 extends Minishell 1 by adding full inter-process communication pipelines and file redirections.**

---

## ⚙️ Advanced Features

- **Pipelines (`|`):** Connects the standard output of a process to the standard input of another using `pipe()` and `dup2()`.
- **Output Redirection (`>` and `>>`):** Redirects stdout to target file in truncate or append mode.
- **Input Redirection (`<` and `<<`):** Redirects stdin from a file or collects multi-line heredoc input until a delimiter is encountered.
- **Semicolon Separator (`;`):** Executes multiple independent commands sequentially.

---

## 🛠️ Build & Usage

```bash
make
./mysh
```

---

## 📜 License

Licensed under the **MIT License with attribution** to Lucas Lhomme (Crabe).
