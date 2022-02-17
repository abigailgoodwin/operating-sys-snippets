# operating-sys-snippets
A collection of programs/scripts that I've written while studying operating systems.

## Contents
### BinaryScan
A short program that parses a binary file, full of integers, to determine the min and max.

#### Usage
* From the commandline, run: ```hw3 <numForks> <file>```
* ```<numForks>``` must be an integer from 1 to and including 4.
* ```<file>``` must be the file path to a binary file.


#### Features
* Generates ```<numForks>``` number of forks to parse the given ```<file>```.
* Not parallel computing; simply a practice of using forks.
* Included in ```binaries/``` is ```genFile.c```, which generates the binary files of integers.
