/**
*
* Solution to homework task
* Data Structures Course
* Faculty of Mathematics and Informatics of Sofia University
* Winter semester 2016/2017
*
* @author Kamen Ivanov
* @idnumber 61894
* @task 0
* @compiler VC
*
*/

#ifndef SPECIAL_CONSTANTS_DECLARATIONS_H
#define SPECIAL_CONSTANTS_DECLARATIONS_H

namespace specialConstants
{
	extern const char initialSymbolOfSpecialString;

	extern const char randomWhiteCharacter[];
	extern const char randomDigit[];
	extern const char randomLetter[];
	extern const char emptyWord[];
	extern const char backSlash[];

	extern const int numberOfSpecialStrings;

	extern const char *const listOfSpecialStrings[];

	extern const char symbolForUnion;
	extern const char symbolForConcatenation ;
	extern const char symbolForClosure;
	extern const char leftParenthese;
	extern const char rightParenthese ;



	extern const int numberOfSymbolsWithWhichARegularExpressionCanNotStart;

	extern const char listOfSymbolsWithWhichARegularExpressionCanNotStart[];


	extern const int numberOfSymbolsWithWhichARegularExpressionCanNotEnd;

	extern const char listOfSymbolsWithWhichARegularExpressionCanNotEnd[];



	extern const int numberOfSymbolsAfterWhichARegularExpressionMustStart;

	extern const char listOfSymbolsAfterWhichARegularExpressionMustStart[];


	const char firstValidSymbolInTheRegularExpression = 33;
	const char lastValidSymbolInTheRegularExpression = 126;



	bool isSymbolWithWhichARegularExpressionCanNotStart(char symbol);

	bool isSymbolWithWhichARegularExpressionCanNotEnd(char symbol);

	bool isSymbolAfterWhichARegularExpressionMustStart(char symbol);

	bool isSpecialString(const char *str);

}

#endif //SPECIAL_CONSTANTS_DECLARATIONS_H