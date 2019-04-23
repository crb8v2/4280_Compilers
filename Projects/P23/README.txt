#################
### Connor Baniak
### 4280 - P1
#################

This project is using option 3. An FSA table and driver
are used to preform lexical analysis.

GITHUB:
    https://github.com/crb8v2/4280_Compilers/tree/master/Projects/P1

SUMMARY:
    Lexical analysis was used to parse a code segment into tokens.
    Using the finite state automata table, INTTK, IDTK, SYMTK, and EOFTK
    were determined.

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
    none

