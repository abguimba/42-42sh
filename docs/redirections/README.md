# 3.4 Redirections

- [3.4.1 Redirecting Input](#341-redirecting-input)
- [3.4.2 Redirecting Output](#342-redirecting-output)
- [3.4.3 Here-Document](#343-here-document)
- [3.4.4 Duplicating an Input File Descriptor](#344-duplicating-an-input-file-descriptor)
- [3.4.5 Duplicating an Output File Descriptor](#345-duplicating-an-output-file-descriptor)

## 3.4.1 Redirecting Input

Input redirection shall cause the file whose name results from the expansion of `word` to be opened for reading on the designated file descriptor, or standard input if the file descriptor is not specified.

The format for redirecting input is:

```
[n]<word
```

Where the optional `n` represents the file descriptor number. If the number is omitted, the redirection shall refer to standard input (file descriptor 0).

Return to index: [Redirections](#34-Redirections), [42sh](../#42sh)

## 3.4.2 Redirecting Output

The two general formats for redirecting output are:

```
[n]>word
```

Where the optional *n* represents the file descriptor number. If the number is omitted, the redirection shall refer to standard output (file descriptor 1).

Return to index: [Redirections](#34-Redirections), [42sh](../#42sh)

## 3.4.3 Here-Document

The here-document shall be treated as a single word that begins after the next <newline> and continues until there is a line containing only the delimiter and a <newline>, with no <blank> characters in between. Then the next here-document starts, if there is one. The format is as follows:

```
[n]<<word
    here-document
delimiter
```

Where the optional `n` represents the file descriptor number. If the number is omitted, the here-document refers to standard input (file descriptor 0). It is unspecified whether the file descriptor is opened as a regular file, a special file, or a pipe. Portable applications cannot rely on the file descriptor being seekable.

Return to index: [Redirections](#34-Redirections), [42sh](../#42sh)

## 3.4.4 Duplicating an Input File Descriptor

The redirection operator:

```
[n]<&word
```

shall duplicate one input file descriptor from another, or shall close one. If `word` evaluates to one or more digits, the file descriptor denoted by `n`, or standard input if `n` is not specified, shall be made to be a copy of the file descriptor denoted by `word`; if the digits in `word` do not represent a file descriptor already open for input, a redirection error shall result.

If `word` evaluates to `-`, file descriptor `n`, or standard input if `n` is not specified, shall be closed.

Return to index: [Redirections](34-#Redirections), [42sh](../#42sh)

## 3.4.5 Duplicating an Output File Descriptor

The redirection operator:

```
[n]>&word
```

shall duplicate one output file descriptor from another, or shall close one. If `word` evaluates to one or more digits, the file descriptor denoted by `n`, or standard output if `n` is not specified, shall be made to be a copy of the file descriptor denoted by `word`; if the digits in `word` do not represent a file descriptor already open for output, a redirection error shall result.

 If 'word' evaluates to `-`, file descriptor `n`, or standard output if `n` is not specified, is closed.

Return to index: [Redirections](#34-redirections), [42sh](../#42sh)

