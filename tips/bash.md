####_How to expand alias command after watch?_

>Aliases are only expanded as the first argument, or after another alias with a trailing space on the end of the command.

>From bash's help alias:

>>A trailing space in VALUE causes the next word to be checked for alias substitution when the alias is expanded.

>To do this, try the following:
```
alias watch='watch '
alias ll='ls -l --color=tty'
watch ll
```