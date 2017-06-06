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

#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include "stackSpecification.h"
#include "deterministicAutomaton.h"
#include "operationOrSimpleRegularExpression.h"
#include "stringSpecification.h"

using namespace std;
using namespace fmi::sdp;
using namespace specialConstants;

//checks if:
//1) all the symbols in the regular expression are valid
//2) is the syntax of the regular expression is correct
//!!!doesn't check for parantheses dismatch
bool checkIfTheRegularExpressionIsValid(const char *regularExpression);

//oldRegularExpression must me a valid regular expression in every other aspect 
//except for the parantheses matching!!!
//
//newRegularExpression will become the same regular expression as 
//oldRegularExpression with the difference that the concatenationSymbol
//will be added everywhere it can, as long as newRegularExpression
//remains a valid regular expression
void makeRegularExpressionWhichIsReadyForConversionIntoPostfixNotation
(char *newRegularExpression, const char *oldRegularExpression);


bool convertTheRegularExpressionIntoPostfixNotation
(const char *regularExpressionString
, Stack<OperationOrSimpleRegularExpression> &regularExpressionInPostfixNotation);


//evaluates the regular expression that we've constructed into an automaton stack
void getDeterministicAutomatonEquivalentToTheRegularExpression
(Stack <DeterministicAutomaton> &automatonStack
, Stack <OperationOrSimpleRegularExpression> &regularExpressionInPostfixNotation);


//if nameOfFileOrDirectory is a name of file,
//then the automaton scans the file;
//else if nameOfFileOrDirectory is a name of a directory,
//then the automaton scans all files in the firectory
//including the files in the subdirectories;
//else prints out an error message
void scanningFilesWithDeterministicAutomaton
(const String &nameOfFileOrDirectory, const DeterministicAutomaton &automaton);


//this is the function that coordinates all other functions in the program

//if nameOfFileOrDirectory is valid and
//initialRegularExpression is a valid regular expression
//the function scans through all the files in the directory
//and prints out the lines, that correspond to the regular expression;
//else prints out an error mesage and returns false
bool scanTheFileOrDirectoryForTheRegularExpression
(const char *nameOfFileOrDirectory, const char *initialRegularExpressionString)
{
	//this function coordinates the sequence of all functions involved in:
	//1)validating if initialRegularExpressionString is a valid regular expression
	//2)converting the regular expression into a postfix regular expression
	//3)constructing a deterministic automaton using the postfix expression
	//4)scanning the file or all files in the directory to find lines corresponding
	//to the regular expression

	bool result = checkIfTheRegularExpressionIsValid(initialRegularExpressionString);

	//if the string isn't a valid regular expression
	if (result == false)
	{
		cerr << initialRegularExpressionString << " isn't a valid regular expression\n";
		return false;
	}

	//this string will contain the same symbols as initialRegularExpression
	//and an additional number of concatenation symbols
	//The number of the concatenation symbols is smaller than the length of 
	//initialRegularExpression
	char *regularExpressionStringReadyForConversionIntoPostfixNotation
		= new char[2 * (strlen(initialRegularExpressionString) + 1)];

	
	makeRegularExpressionWhichIsReadyForConversionIntoPostfixNotation
		(regularExpressionStringReadyForConversionIntoPostfixNotation,
		initialRegularExpressionString);

	//cout << regularExpressionStringReadyForConversionIntoPostfixNotation << endl;

	/*
		Now, everything is ready for us to apply the shunting yard
		algirithm.
	*/

	Stack<OperationOrSimpleRegularExpression> regularExpressionInPostfixNotation;

	result = convertTheRegularExpressionIntoPostfixNotation
		(regularExpressionStringReadyForConversionIntoPostfixNotation
		, regularExpressionInPostfixNotation);
	
	//we don't need this string anymore
	delete[] regularExpressionStringReadyForConversionIntoPostfixNotation;
	
	if (result == false)
	{
		cerr << initialRegularExpressionString << " isn't a valid regular expression\n";
		return false;
	}

	Stack<DeterministicAutomaton> automatonStack;

	try
	{
	
	getDeterministicAutomatonEquivalentToTheRegularExpression
		(automatonStack
		, regularExpressionInPostfixNotation);
	}
	catch (const exception &except)
	{
		cerr << initialRegularExpressionString << " isn't a valid regular expression\n";
		return false;
	}

	DeterministicAutomaton automaton;

	//if the regular expression isn't an empty string(""),
	//then the automaton stack shuld have exactly
	//one element if the regular expression is correct
	if (!automatonStack.isEmpty())
	{
		automaton = automatonStack.pop();
	}

	if (!automatonStack.isEmpty())
	{
		cerr << initialRegularExpressionString << " isn't a valid regular expression\n";
		return false;
	}

	scanningFilesWithDeterministicAutomaton
		(nameOfFileOrDirectory, automaton);

	return true;
}