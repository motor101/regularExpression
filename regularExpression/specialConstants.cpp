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

#include<cstring>

namespace specialConstants
{
	extern const char initialSymbolOfSpecialString = '\\';

	extern const char randomWhiteCharacter[3] = { initialSymbolOfSpecialString, 's', '\0'};
	extern const char randomDigit[3] =			{ initialSymbolOfSpecialString, 'd', '\0' };
	extern const char randomLetter[3] =			{ initialSymbolOfSpecialString, 'a', '\0' };
	extern const char emptyWord[3] =			{ initialSymbolOfSpecialString, 'e', '\0' };
	extern const char backSlash[3] =			{ initialSymbolOfSpecialString, '\\', '\0' };

	extern const int numberOfSpecialStrings = 5;

	extern const char *const listOfSpecialStrings[numberOfSpecialStrings]
		= { randomWhiteCharacter, randomDigit, randomLetter, emptyWord, backSlash };


	extern const char symbolForUnion = '|';
	extern const char symbolForConcatenation = '.';
	extern const char symbolForClosure = '*';
	extern const char leftParenthese = '(';
	extern const char rightParenthese = ')';


	extern const int numberOfSymbolsWithWhichARegularExpressionCanNotStart = 4;

	extern const char listOfSymbolsWithWhichARegularExpressionCanNotStart
		[numberOfSymbolsWithWhichARegularExpressionCanNotStart]
	= { symbolForUnion, symbolForConcatenation, symbolForClosure, rightParenthese };


	extern const int numberOfSymbolsWithWhichARegularExpressionCanNotEnd = 3;

	extern const char listOfSymbolsWithWhichARegularExpressionCanNotEnd
		[numberOfSymbolsWithWhichARegularExpressionCanNotEnd]
	= { symbolForUnion, symbolForConcatenation, leftParenthese };


	extern const int numberOfSymbolsAfterWhichARegularExpressionMustStart = 3;

	extern const char listOfSymbolsAfterWhichARegularExpressionMustStart
		[numberOfSymbolsAfterWhichARegularExpressionMustStart]
	= { symbolForUnion, symbolForConcatenation, leftParenthese };


	bool isSpecialString(const char *str)
	{
		for (int i = 0; i < numberOfSpecialStrings; ++i)
		{
			if (strcmp(str, listOfSpecialStrings[i]) == 0)
			{
				return true;
			}
		}

		return false;
	}

	bool isSymbolWithWhichARegularExpressionCanNotStart(char symbol)
	{
		for (int i = 0; i < numberOfSymbolsWithWhichARegularExpressionCanNotStart; ++i)
		{
			if (symbol == listOfSymbolsWithWhichARegularExpressionCanNotStart[i])
				return true;
		}

		return false;
	}

	bool isSymbolWithWhichARegularExpressionCanNotEnd(char symbol)
	{
		for (int i = 0; i < numberOfSymbolsWithWhichARegularExpressionCanNotEnd; ++i)
		{
			if (symbol == listOfSymbolsWithWhichARegularExpressionCanNotEnd[i])
				return true;
		}

		return false;
	}

	bool isSymbolAfterWhichARegularExpressionMustStart(char symbol)
	{
		for (int i = 0; i < numberOfSymbolsAfterWhichARegularExpressionMustStart;++i)
		{
			if (symbol == listOfSymbolsAfterWhichARegularExpressionMustStart[i])
			{
				return true;
			}
		}

		return false;
	}
}