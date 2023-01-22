## Features
* Prints user and current directory.
* No need to enter the full path of the command as this shell parses automatically the env variable PATH and searches in their directories.
* It gives an error if the command was not found

## Known issues
* The shell handles only first command, then it throws always ann error that command was not found.
* It parses the command argument but they are not executed, i.e. `ls -l` is accepted, but the output is the result of `ls` only.