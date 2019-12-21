# 42sh

This project consists of creating a complete shell and uses the work done on [21sh](https://github.com/mjose-portfolio/42-21sh#21sh) and [minishell](https://github.com/mjose-portfolio/42-minishell#minishell) projects. We build our own shell, including a job control and shell script. This project involves a large variety of standard UNIX (and POSIX) functionalities.

## 1. Project Partners

------

- [Abraham Gimbao](https://github.com/abguimba)
- [Alexandre Somville](https://github.com/alsomvil42)
- [Brendan Siche](https://github.com/BrendanSiche)
- [Marc Jose](https://github.com/mjose-portfolio)

## 2. Install
------

- `make`

![alt text](README_resources/make.gif)

### 2.1. Make Options

- `make`: Compiles the files and creates the executable 42sh
- `make clean`: Remove binary files.
- `make fclean`: Deletes the binary files and the 42sh executable file.
- `make re`: Deletes the binary files and the 42sh executable file and recompiles them.

## 3. Features
------
### 3.1 Builtins

- [3.1.1 alias](./builtins#311-alias)
- [3.1.2 bg](./builtins#312-bg)
- [3.1.3 cd](./builtins#313-cd)
- [3.1.4 echo](./builtins#314-echo)
- [3.1.5 env](./builtins#315-env)
- [3.1.6 exit](./builtins#316-exit--n-)
- [3.1.7 export](./builtins#317-export)
- [3.1.8 false](./builtins#318-false)
- [3.1.9 fg](./builtins#319-fg)
- [3.1.10 hash](./builtins#3110-hash)
- [3.1.11 history](./builtins#3111-history)
- [3.1.12 jobs](./builtins#3112-jobs)
- [3.1.13 set](./builtins#3113-set)
- [3.1.14 test](./builtins#3114-test)
- [3.1.15 true](./builtins#3115-true)
- [3.1.16 type](./builtins#3116-type)
- [3.1.17 unalias](./builtins#3117-unalias)
- [3.1.18 unset](./builtins#3118-unset)
- [3.1.19 fc](./builtins#3119-fc)

### 3.2 Prompt

The prompt is displayed as follows:

- `["user"]<"current directory">42sh $/>`

The current directory is updated live, each time you change directory, of course, the information is collected from the environment variable `PWD`.

### 3.3 Execution of Commands

The command shall be searched for using the PATH environment variable.

It is possible to specify the paths where the command to execute resides (in case you want to execute a command that does not reside in any directory of the PATH variable, or the variable is not defined).

The parameters of each command are taken into account.

### 3.4 Redirections

- [3.4.1 Redirecting Input](./redirections#341-redirecting-input)
- [3.4.2 Redirecting Output](./redirections#342-redirecting-output)
- [3.4.3 Here-Document](./redirections#343-here-document)
- [3.4.4 Duplicating an Input File Descriptor](./redirections#344-duplicating-an-input-file-descriptor)
- [3.4.5 Duplicating an Output File Descriptor](./redirections#345-duplicating-an-output-file-descriptor)

### 3.5 Pipelines

The format for a pipeline is:

```
command1 [ | command2 ...]
```

The standard output of `command1` shall be connected to the standard input of `command2`. The standard input, standard output, or both of a command shall be considered to be assigned by the pipeline before any redirection specified by redirection operators that are part of the command.

### 3.6 `;` Operand

it is possible to separate commands using the operand `;`.

```
command1 ; command2 ...
```

### 3.7 Management Of Internal Variables

- Creation of internal variables according to the syntax:

```
name=value
```

- Export of internal variables to the environment, via built-in [export](./builtins#317-export).
- List the internal variables of the shell via the built-in [set]((./builtins#3113-set)).
- Removal of internal and environmental variables, via the built-in [unset](./builtins#3118-unset).
- Creation of environment variables for a single command, example :

```
HOME=/tmp cd
```

- Simple expansion of parameters according to the syntax:

```
${name}
$name
```

- Management of special parameters:

```
$: PID of the current process.
?: Last command exit code.
0: Shell name.
!: PID of the last process launched in backround.
_: Last parameter used in a command.
```

### 3.8 Job Control Management

The builtins that allow to interact with the Job Control are:

- [bg](./builtins#312-bg)
- [fg](./builtins#319-fg)
- [jobs](./builtins#3112-jobs)

### 3.9 Inhibitors

- Single-quotes: `'`

  Enclosing characters in single-quotes ( `''` ) shall preserve the literal value of each character within the single-quotes. A single-quote cannot occur within single-quotes.

- Double-quotes:`"`

  Enclosing characters in double-quotes ( `""` ) shall preserve the literal value of all characters within the double-quotes, with the exception of the characters backquote, <dollar-sign>, and <backslash>.

- Escape Character (Backslash): `\`

   A <backslash> that is not quoted shall preserve the literal value of the following character, with the exception of a <newline>. If a <newline> follows the <backslash>, the shell shall interpret this as line continuation. The <backslash> and <newline> shall be removed before splitting the input into tokens. Since the escaped <newline> is removed entirely from the input and is not replaced by any white space, it cannot serve as a token separator.

### 3.10 Parameter Expansions

```
${parameter:-[word]}
```

**Use Default Values**. If *parameter* is unset or null, the expansion of *word* (or an empty string if *word* is omitted) shall be substituted; otherwise, the value of *parameter* shall be substituted.

```
${parameter:=[word]}
```

**Assign Default Values**. If *parameter* is unset or null, the expansion of *word* (or an empty string if *word* is omitted) shall be assigned to *parameter*. In all cases, the final value of *parameter* shall be substituted. Only variables, not positional parameters or special parameters, can be assigned in this way.

```
${parameter:?[word]}
```

**Indicate Error if Null or Unset**. If *parameter* is unset or null, the expansion of *word* (or a message indicating it is unset if *word* is omitted) shall be written to standard error and the shell exits with a non-zero exit status. Otherwise, the value of *parameter* shall be substituted. An interactive shell need not exit.

```
${parameter:+[word]}
```

**Use Alternative Value**. If *parameter* is unset or null, null shall be substituted; otherwise, the expansion of *word* (or an empty string if *word* is omitted) shall be substituted.

```
${#parameter}
```

**String Length**. The length in characters of the value of *parameter* shall be substituted. If *parameter* is `'*'` or `'@'`, the result of the expansion is unspecified. If *parameter* is unset and [*set*](https://pubs.opengroup.org/onlinepubs/9699919799//utilities/V3_chap02.html#set) **-u** is in effect, the expansion shall fail.

```
${parameter%[word]}
```

**Remove Smallest Suffix Pattern**. The *word* shall be expanded to produce a pattern. The parameter expansion shall then result in *parameter*, with the smallest portion of the suffix matched by the *pattern* deleted. If present, *word* shall not begin with an unquoted `'%'`.

```
${parameter%%[word]}
```

**Remove Largest Suffix Pattern**. The *word* shall be expanded to produce a pattern. The parameter expansion shall then result in *parameter*, with the largest portion of the suffix matched by the *pattern* deleted.

```
${parameter#[word]}
```

**Remove Smallest Prefix Pattern**. The *word* shall be expanded to produce a pattern. The parameter expansion shall then result in *parameter*, with the smallest portion of the prefix matched by the *pattern* deleted. If present, *word* shall not begin with an unquoted `'#'`.

```
${parameter##[word]}
```

**Remove Largest Prefix Pattern**. The *word* shall be expanded to produce a pattern. The parameter expansion shall then result in *parameter*, with the largest portion of the prefix matched by the *pattern* deleted.

```
~
```

**HOME path of the current user.** Is replaced by the HOME path of the current user

```
~[user name]
```

**HOME path of the user name.**  The tilde-prefix is replaced with the home directory associated with the specified user name.

```
~+
```

**PWD value**. the value of the [shell variable] `PWD` replaces the tilde-prefix.

```
~-
```

**OLDPWD value**. the value of the [shell variable] `OLDPWD` replaces the tilde-prefix.

### 3.11 History Management

Executed commands are automatically saved in the `$HOME/.42hist` file, so that they can be used from other sessions.

Incremental search in the history with the key combination `CTRL-R`.

The builtin that allow to interact with the Job Control is:

- [fc](./builtins#3119-fc)

It is also possible to navigate through the history with the `up and down arrow keys`.

#### 3.11.1 History Expansions

```
!
```

Start a history substitution, except when followed by a space, tab, the end of the line, `=` or `(`.

```
!!
```

Refer to the previous command. This is a synonym for `!-1`.

```
![word]
```

Refer to the most recent command preceding the current position in the history list starting with `word`.

```
![number]
```

Refer to command line `number`.

```
!-[numer]
```

Refer to the command `n` lines back.

### 3.12 Contextual Dynamic Completion

It is possible to autocomplete variables, file commands, by pressing the 'TAB key', whether or not the command has been typed.

### 3.13 Command line

The command line features are:

- Edit the line where the cursor is located.
- Move the cursor left and right to be able to edit the line at a specific location.
- Use `up and down arrows` to navigate through the command history able to edit if we feel like it.
- Cut, copy, and/or paste all or part of a line whit `cmd+f1`, `cmd+f2` and `cmd+f3`
- Move directly by word towards the left or the right using `shift+LEFT` and `shift+RIGHT`.
- Go directly to the beginning or the end of a line by pressing `fn+left` and `fn+right`.
- Write and edit a command over a few lines.
