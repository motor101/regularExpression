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

Example:
> RegExSearch.exe MyFile.txt "(a*)"
MyFile.txt:5:aaaaaa
MyFile.txt:15:aaa
MyFile.txt:16:aaaaaaaaaa
