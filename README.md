# Minibash

## table of contents

- [table of contents](#table-of-contents)
- [description](#description)
- [how it works](#how-it-works)
- [usage](#usage)

## description

Minibash is a simple shell written in C. It is a project for the 42 school.

Everything is written from scratch, including the parser, the lexer, the execution of the commands, the builtins, the signals, the redirections, the pipes, the env variables, the aliases, the expansion of the variables and so on.

The goal of this project is for us to understand how a shell works and how to use the system calls.
It is also a good way to learn about the C language and the builtin functions our OS offers us.

Everything is written in accordance with the 42 norm.

## how it works

The shell is launched by typing `./minibash` in the terminal. It will then display a prompt and wait for the user to type a command.

The command is firstly split into tokens using the lexer. Then, the parser will check if the command is valid and will split it into different parts if necessary (redirections, pipes, etc.).
It will also expand the variables and the aliases.

Once we have a valid command, we will check if it is a builtin (one we haven't rebuild). If it is, we will execute it. Otherwise, we will fork the process and execute the command in the child process using our own implentation of the `execve` function.

After the execution of the command, we will free all the memory we allocated and we will loop back to the beginning where you will again face a prompt.

The shell supports the following builtins:

- `echo`
- `cd`
- `pwd`
- `export`
- `unset`
- `env`
- `exit`
- The ones we havent implemented will be executed by the system using the "PATH" variable.

The redirections that are supported:
- `>` 
- `>>` 
- `<`
- `<<`

And the following symbols:

- `|`
- `$`
- `$$`

## usage

Type 'make' to compile the program.

Run it with './minishell'.
