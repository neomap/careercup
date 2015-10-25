###Tips

* How to restore default .bashrc file?
`cp /etc/skel/.bashrc ~/`

* Linux Directory Structure explained
Wikipedia page [Filesystem Hierarchy Standards][1], and there is a group
to define specification for [FHS][3].
Link from [thegeekstuff][2] explains this with examples.
Shell command `man hier` explains basic layout of unix filesystems.

### Introduction to tools
- <b> flex

>flex is a tool for generating scanners: programs which recognize lexical patterns in text. flex reads the given input files (or its standard input if no file names are given) for a description of the scanner to generate. The description is in the form of pairs of regular expressions and C code, called rules. flex generates as output a C source file, `lex.yy.c', which defines a routine yylex. Compile and link this file with the `-lfl' library to produce an executable. When the executable runs, it analyzes its input for occurrences of the regular expressions. Whenever it finds one, it executes the corresponding C code. 

[1]: https://en.wikipedia.org/wiki/Filesystem_Hierarchy_Standard
[2]: http://www.thegeekstuff.com/2010/09/linux-file-system-structure/
[3]: http://refspecs.linuxfoundation.org/fhs.shtml