# Builtins

- [3.1.1 alias](#311-alias)
- [3.1.2 bg](#312-bg)
- [3.1.3 cd](#313-cd)
  * [3.1.3.1 Options](#3131-options)
- [3.1.4 echo](#314-echo)
- [3.1.5 env](#315-env)
  * [3.1.5.1 Options](#3151-options)
- [3.1.6 exit [n]](#316-exit--n-)
- [3.1.7 export](#317-export)
  * [3.1.7.1 Options](#3171-options)
- [3.1.8 false](#318-false)
- [3.1.9 fg](#319-fg)
- [3.1.10 hash](#3110-hash)
  * [3.1.10.1 Options](#31101-options)
- [3.1.11 history](#3111-history)
  * [3.1.11.1 Options](#31111-options)
- [3.1.12 jobs](#3112-jobs)
  * [3.1.12.1 Options](#31121-options)
- [3.1.13 set](#3113-set)
- [3.1.14 test](#3114-test)
  * [3.1.14.1 Options](#31141-options)
- [3.1.15 true](#3115-true)
- [3.1.16 type](#3116-type)
- [3.1.17 unalias](#3117-unalias)
  * [3.1.17.1 Options](#31171-options)
- [3.1.18 unset](#3118-unset)
- [3.1.19 fc](#3119-fc)
  * [3.1.19.1 Options](#31191-fc)

#### 3.1.1 alias

------

Without arguments, `alias` prints the list of aliases on the standard output. If arguments are supplied, an alias is defined for each name whose value is given. If no value is given, the name and value of the alias is printed.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.2 bg

------

Resume each suspended job in the background, as if it had been started with &.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

Return to section: [3.8 Job Control Management](../#38-job-control-management)

#### 3.1.3 cd

------

Change the current working directory to `directory`. If `directory` is not supplied, the value of the `HOME` shell variable is used.

##### 3.1.3.1 Options

`-L`: symbolic links in directory are resolved after `cd` processes an instance of ‘`..`’ in directory.

`-P`: not follow symbolic links: symbolic links are resolved while `cd` is traversing `directory` and before processing an instance of ‘`..`’ in directory.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.4 echo

------

Outputs it's args to stdout, separated by spaces, followed by a newline. The return status is always 0.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.5 env

------

Set the environment for command invocation.

##### 3.1.5.1 Options

`-i`: Invoke utility with exactly the environment specified by the arguments; the inherited environment shall be ignored completely.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.6 exit [n]

------

Shall cause the shell to exit with the exit status specified by the unsigned decimal integer n.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.7 export

------

Marks an environment variable to be exported with any newly forked child processes and thus it allows a child process to inherit all marked variables.

##### 3.1.7.1 Options

`-p`: List of all names that are exported in the current shell.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.8 false

------

Do nothing, returning a non-zero (false) exit status.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.9 fg

------

Put each specified job in the background, or the current job if none is specified.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

Return to section: [3.8 Job Control Management](../#38-job-control-management)

#### 3.1.10 hash

------

Determine and remember the full pathname of each commandname. If no arguments are given, display information about remembered command locations.

#### 3.1.10.1 Options

`-r`: Forget all remembered locations.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.11 history

------

With no options, display the history list with line numbers.

##### 3.1.11.1 Options

`-c`: Clear the history list.

`-d [offset]`: Delete the history entry at position `offset`. `offset` should be specified as it appears when the history is displayed.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.12 jobs

------

The first form lists the active jobs.

##### 3.1.12.1 Options

`-p`: List only the process ID of the job’s process group leader.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

Return to section: [3.8 Job Control Management](../#38-job-control-management)

#### 3.1.13 set

------

Change the value of a shell option and set the positional parameters, or display the names and values of shell variables.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.14 test

------

 Evaluate a conditional expression.

##### 3.1.14.1 Options

`-b [pathname]`: True if `pathname` resolves to an existing directory entry for a block special file. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a block special file.

`-c [pathname]`: True if `pathname` resolves to an existing directory entry for a character special file. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a character special file.

`-d [pathname]`: True if `pathname` resolves to an existing directory entry for a directory. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a directory.

`-e [pathname]`: True if `pathname` resolves to an existing directory entry. False if `pathname` cannot be resolved.

`-f [pathname]`: True if `pathname` resolves to an existing directory entry for a regular file. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a regular file.

`-g [pathname]`: True if `pathname` resolves to an existing directory entry for a file that has its set-group-ID flag set. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that does not have its set-group-ID flag set.

`-L [pathname]`: True if `pathname` resolves to an existing directory entry for a symbolic link. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a symbolic link. If the final component of `pathname` is a symbolic link, that symbolic link is not followed.

`-p [pathname]`: True if `pathname` resolves to an existing directory entry for a FIFO. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a FIFO.

`-r [pathname]`: True if `pathname` resolves to an existing directory entry for a file for which permission to read from the file will be granted, as defined in [File Read, Write, and Creation](https://pubs.opengroup.org/onlinepubs/9699919799//utilities/V3_chap01.html#tag_17_01_01_04). False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file for which permission to read from the file will not be granted.

`-S [pathname]`: True if `pathname` resolves to an existing directory entry for a socket. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that is not a socket.

`-s [pathname]`: True if `pathname` resolves to an existing directory entry for a file that has a size greater than zero. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that does not have a size greater than zero.

`-u [pathname]`: True if `pathname` resolves to an existing directory entry for a file that has its set-user-ID flag set. False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file that does not have its set-user-ID flag set.

`-w [pathname]`: True if `pathname` resolves to an existing directory entry for a file for which permission to write to the file will be granted, as defined in [File Read, Write, and Creation](https://pubs.opengroup.org/onlinepubs/9699919799//utilities/V3_chap01.html#tag_17_01_01_04). False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file for which permission to write to the file will not be granted.

`-x [pathname]`: True if `pathname` resolves to an existing directory entry for a file for which permission to execute the file (or search it, if it is a directory) will be granted, as defined in [File Read, Write, and Creation](https://pubs.opengroup.org/onlinepubs/9699919799//utilities/V3_chap01.html#tag_17_01_01_04). False if `pathname` cannot be resolved, or if `pathname` resolves to an existing directory entry for a file for which permission to execute (or search) the file will not be granted.

`-z [string]`: True if the length of string `string` is zero; otherwise, false.

`s1 = s2`: True if the strings `s1` and `s2` are identical; otherwise, false.

`s1 != s2`: True if the strings `s1` and `s2` are not identical; otherwise, false.

`n1 -eq n2`: True if the integers `n1` and `n2` are algebraically equal; otherwise, false.

`n1 -ne n2`: True if the integers `n1` and `n2` are not algebraically equal; otherwise, false.

`n1 -gt  n2`: True if the integer `n1` is algebraically greater than the integer `n2`; otherwise, false.

`n1 -ge n2`: True if the integer `n1` is algebraically greater than or equal to the integer `n2`; otherwise, false.

`n1 -lt n2`: True if the integer `n1` is algebraically less than the integer `n2`; otherwise, false.

`n1 -le n2`: True if the integer `n1` is algebraically less than or equal to the integer `n2`; otherwise, false.

`! [expression]`: True if `expression` is false. False if `expression` is true.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.15 true

------

Does nothing except return an exit status of 0, meaning "success". 

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.16 type

------

Describe a command. For each *name*, indicate how it would be interpreted if used as a command name.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.17 unalias

------

Remove each name from the list of aliases.

##### 3.1.17.1 Options

`-a`: all aliases are removed.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.18 unset

------

Remove variable.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

#### 3.1.19 fc

------

Process the command history list.

##### 3.1.19.1 Options

`-e [editor]`: Use the editor named by `editor` to edit the commands. The `editor` string is a utility name, subject to search via the `PATH` variable. The value in the `FCEDIT` variable shall be used as a default when **-e** is not specified. If `FCEDIT` is null or unset, `ed` shall be used as the editor.

`-l`: List the commands rather than invoking an editor on them. The commands shall be written in the sequence indicated by the *first* and *last* operands, as affected by **-r**, with each command preceded by the command number.

`-n`: Suppress command numbers when listing with `-l`.

`-r`: Reverse the order of the commands listed (with `-l`) or edited (with neither `-l` nor `-s`).

`-s`: Re-execute the command without invoking an editor.

Return to index: [Builtins](#Builtins), [42sh](../#42sh)

Return to section: [3.11 History Management](../#311-history-management)