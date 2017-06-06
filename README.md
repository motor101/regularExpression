# regularExpression

Input:
1) name of file or name of directory
2) regular expression

Result:
Scans the file or all the files in the directory and prints out the lines which correspond to the regular expression.

Algorithm:
1) Constructs a finite state automaton, which recognizes the language of the regular expression.
i.e. Language(automaton) = Language(regular expression)
2) Scan the files recursively with the automaton.

Alphabet of the regular expression:
1)all lowercase and uppercase letters
2)all digits
3)special strings ::= \s \d \a \e \\
4)basic symbols ::= | . * \

Special strings:
\s is a random whitespace character
\d is a random digit
\a is a random letter (lowercase or uppercase)
\e is the empty word
\\ is a dash(\)

Basic symbols:
| is the union operation
. is the concatenation operation
\* is the iteration operation
\ is the initial symbol of a special string

Example:
>RegExSearch.exe MyFile.txt a*
MyFile.txt:5:aaaaaaa
MyFile.txt:11:aa
MyFile.txt:21:aaaaaaaaaaa

>RegExSearch.exe MyFile.txt a*|b*
MyFile.txt:5:aaaaa
MyFile.txt:13:bbb
MyFile.txt:32:bbbbbbbb

>RegExSearch.exe MyFile.txt \a.\d*|a*\e\a*
MyFile.txt:5:a24234234
MyFile.txt:f242
MyFile.txt:21:g
MyFile.txt:32:gsafsdfsf asdfasdsdf
MyFile.txt:55:ertoert eyrgefb
