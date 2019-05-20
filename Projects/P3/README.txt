#################
### Connor Baniak
### 4280 - P2
#################

This project parses the test file for syntax and then builds a tree.

GITHUB:
    https://github.com/crb8v2/4280_Compilers/tree/master/Projects/P2

SUMMARY:


INPUT:
    No IDTK is allowed to start with a lowercase letter.

    Alphabet made of: Uppercase letters, lowercase letters, digits,
    and symbols ('=','<','>', ':', '+', '-', '*', '/', '%', '.', '(', ')',
    ',', '{', '}', ';', '[', ']').

    Keywords follow: Begin, End, Loop, Void, INT, Return, Read,
    Output, Program, IFF, Then, Let

USAGE:
    ./scanner                                   allows user input
    ./scanner < [filename]                      pipes input from file
    ./scanner [filename w/o file extension]     takes filename and appends .input1

FIXES:
    parses vars():
	need to fix stats():

