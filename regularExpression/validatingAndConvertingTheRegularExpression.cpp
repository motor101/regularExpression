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
#include <cstring>
#include <cassert>
#include <stdexcept>
#include "specialConstantsDeclarations.h"
#include "Operation.h"
#include "operationOrSimpleRegularExpression.h"
#include "stackSpecification.h"
#include "deterministicAutomaton.h"

using namespace std;
using namespace specialConstants;
using namespace fmi::sdp;

//evaluates the regular expression that we've constructed into an automaton stack
void getDeterministicAutomatonEquivalentToTheRegularExpression
( Stack <DeterministicAutomaton> &automatonStack
, Stack <OperationOrSimpleRegularExpression> &regularExpressionInPostfixNotation)
{
	OperationOrSimpleRegularExpression operationOrRegExpression;

	DeterministicAutomaton automaton1;

	DeterministicAutomaton automaton2;

	while (!regularExpressionInPostfixNotation.isEmpty())
	{
		//get the element on top of the stack
		operationOrRegExpression = regularExpressionInPostfixNotation.pop();

		//read the element on top of the stack

		if (operationOrRegExpression.type == TYPE_IS_SIMPLE_REG_EX)
		{
			automatonStack.push(operationOrRegExpression.notation);
		}
		else //the current element is an operation
		{
			//every operation is represented by a symbol, so we'll
			//only need notation[0]

			if (operationOrRegExpression.notation[0] == symbolForClosure)
			{
				automaton1 = automatonStack.pop();
				automatonStack.push(DeterministicAutomaton::makeClosure(automaton1));
			}
			else
			{
				automaton2 = automatonStack.pop();
				automaton1 = automatonStack.pop();

				if (operationOrRegExpression.notation[0] == symbolForConcatenation)
				{
					automatonStack
						.push(DeterministicAutomaton::makeConcatenation(automaton1, automaton2));
				}
				else if (operationOrRegExpression.notation[0] == symbolForUnion)
				{
					automatonStack
						.push(DeterministicAutomaton::makeUnion(automaton1, automaton2));
				}
				else
				{
					assert(false);
				}
			}
		}
	}
}

//checks if some of the strings in listOfSpecialStrings is a prefix of str
//if such string is found in the list, the function returns its index
//if such string isn't found, the function returns -1
int getIndexOfSpecialStringPrefix(const char* str)
{
	//this variable will be used to iterate through the elements of each string in the list
	int pos;

	for (int i = 0; i < numberOfSpecialStrings; ++i)
	{
		pos = 0;

		//compare the strings str and listOfSpecialStrings[i]
		while (listOfSpecialStrings[i][pos] != '\0')
		{
			//if the two strings are different, there's no need to compare them any more
			if (str[pos] != listOfSpecialStrings[i][pos])
				break;

			++pos;
		}

		//if listOfSpecialStrings[i] is a prefix of str
		if (listOfSpecialStrings[i][pos] == '\0')
		{
			return i;
		}
	}
	
	return -1;
}

//checks if:
//1) all the symbols in the regular expression are valid
//2) is the syntax of the regular expression is correct
//!!!doesn't check for parantheses dismatch
bool checkIfTheRegularExpressionIsValid(const char *regularExpression)
{
	/*
		We'll describe a valid regular expression using this grammar

		<reg. expression> ::= 
		symbol in the interval 
		[firstValidSymbolInTheRegularExpression; lastValidSymbolInTheRegularExpression],
		different than the symbols in the listOfSpecialSymbols
		or
		one of the strings from the listOfSpecialStrings
		or
		<reg. expression><symbolForClosure>
		or
		<reg. expression><symbolForUnion><reg. expression>
		or
		<reg. expression><symbolForConcatenation><reg. expression>
		or
		<leftParanthese><reg. expression><rightParanthese>

		Using this information, we can validate the regular expression, using this rules:
		1) each symbol from the regular expression must be in the interval [first; last]

		2) if the current symbol is the initialSymbolOfSpecialString,
		then the substring, starting from this symbol must be in the listOfSpecialStrings

		3) if the curent symbol is a symbol after which a regular expression must start then
		the next symbol must not be a symbol with which a regular expression can not start

		4) the first symbol can not be a symbol with which a regular expression can not start

		5) the last symbol can not be a symbol with which a regular expression can not end

		6) there must not be a parantheses dismatch

		this function is going to check rules 1) - 5)
	*/

	char currentSymbol;
	char nextSymbol;

	int index = 0;

	while (regularExpression[index] != '\0')
	{
		currentSymbol = regularExpression[index];

		nextSymbol = regularExpression[index + 1];

		//1)
		//if the current symbol isn't a valid symbol
		if (currentSymbol < firstValidSymbolInTheRegularExpression ||
			currentSymbol > lastValidSymbolInTheRegularExpression   )
		{
			cerr << "the symbol " << currentSymbol << " at position "
				 << index << " in the regular expression is invalid\n";
			return false;
		}

		//2)
		if (currentSymbol == initialSymbolOfSpecialString)
		{
			int indexOfSpecialStringPrefix 
				= getIndexOfSpecialStringPrefix( &regularExpression[index]);

			//if the symbols starting from the current index don't make a special string
			if (indexOfSpecialStringPrefix == -1)
			{
				cerr << "the string starting at position " << index << " isn't a valid special string\n";
				return false;
			}
			else
			{
				index += strlen(listOfSpecialStrings[indexOfSpecialStringPrefix]);
				continue;
			}
		}

		//3)
		if (isSymbolAfterWhichARegularExpressionMustStart(currentSymbol) &&
			isSymbolWithWhichARegularExpressionCanNotStart(nextSymbol))
		{
			cerr << "the symbol " << nextSymbol << " must not success the symbol " << currentSymbol << '\n';
			return false;
		}
		 
		++index;
	}
	
	//index is now pointing to the '\0' i.e. the last element of the string

	//if the string isn't an empty string
	//then we're going to check its first and last symbol
	if (index > 0)
	{
		//4)
		if (isSymbolWithWhichARegularExpressionCanNotStart(regularExpression[0]))
		{
			cerr << "the regular expression must not start with the symbol " << regularExpression[0] << '\n';
			return false;
		}

		//5)
		if (isSymbolWithWhichARegularExpressionCanNotEnd(currentSymbol))
		{
			cerr << "the regular expression must not end with the symbol " << currentSymbol << '\n';
			return false;
		}
	}

	return true;
}

//oldRegularExpression must me a valid regular expression in every other aspect 
//except for the parantheses matching!!!
//
//newRegularExpression will become the same regular expression as 
//oldRegularExpression with the difference that the concatenationSymbol
//will be added everywhere it can, as long as newRegularExpression
//remains a valid regular expression
void makeRegularExpressionWhichIsReadyForConversionIntoPostfixNotation
(char *newRegularExpression, const char *oldRegularExpression)
{
	int indexOfNewRegularExpression = 0;
	int indexOfOldRegularExpression = 0;

	char currentSymbol;
	char nextSymbol;

	while (oldRegularExpression[indexOfOldRegularExpression] != '\0')
	{
		currentSymbol = oldRegularExpression[indexOfOldRegularExpression];
		nextSymbol = oldRegularExpression[indexOfOldRegularExpression + 1];

		if (currentSymbol == initialSymbolOfSpecialString)
		{
			int indexOfSpecialStringPrefix
				= getIndexOfSpecialStringPrefix(&oldRegularExpression[indexOfOldRegularExpression]);

			//oldRegularExpression must me a valid regular expression in every other aspect 
			//except for the parantheses matching!!!
			assert(indexOfSpecialStringPrefix != -1);

			int pos = 0;

			while (listOfSpecialStrings[indexOfSpecialStringPrefix][pos++] != '\0')
			{
				newRegularExpression[indexOfNewRegularExpression++]
					= oldRegularExpression[indexOfOldRegularExpression++];
			}

			//if oldRegularExpression[indexOfOldRegularExpression] is a symbol with which
			//a regular expression CAN start and it isn't the last symbol in the oldRegularExpression
			if (isSymbolWithWhichARegularExpressionCanNotStart
				(oldRegularExpression[indexOfOldRegularExpression]) == false
				&&
				oldRegularExpression[indexOfOldRegularExpression] != '\0'
				)
			{
				newRegularExpression[indexOfNewRegularExpression++] = symbolForConcatenation;
			}

			continue;
		}

		//currentSymbol isn't the initial symbol for special strings

		newRegularExpression[indexOfNewRegularExpression++] 
			= oldRegularExpression[indexOfOldRegularExpression++];

		//if currentSymbol is a symbol with which a regular expression CAN end
		//and nextSymbol is a symbol with which a regular expression CAN start
		if (isSymbolWithWhichARegularExpressionCanNotEnd(currentSymbol) == false
			&&
			isSymbolWithWhichARegularExpressionCanNotStart(nextSymbol) == false
			&&
			nextSymbol != '\0'
			)
		{
			newRegularExpression[indexOfNewRegularExpression++] = symbolForConcatenation;
		}
	}

	//we have to terminate the newRegularExpression string
	newRegularExpression[indexOfNewRegularExpression] = '\0';
}

//adds the operation with number indexOfOperation
//to the operation stack, by extracting the operations on top
//of the stack with a higher priority and adding them to
//the postfix regular expression
bool addOperationToListOfOperations
( int indexOfOperation
, Stack<Operation> &operationStack
, Stack<OperationOrSimpleRegularExpression> &regularExpressionInPostfixNotation)
{
	assert(indexOfOperation != -1);

	const Operation &currentOperation = listOfOperations[indexOfOperation];
	
	//this valiable is a buffer
	Operation lastOperationAdded;
	
	if (currentOperation.symbol == rightParenthese)
	{
		if (operationStack.isEmpty())
		{
			cerr << "paranthese dismatch\n";
			return false;
		}

		while (!operationStack.isEmpty())
		{
			lastOperationAdded = operationStack.pop();

			if (lastOperationAdded.symbol == leftParenthese)
			{
				return true;
			}
			else
			{
				regularExpressionInPostfixNotation.push(lastOperationAdded.symbol);
			}
		}

		//operationStack is empty;
		//we went trough all elements in the stack, but couldn't find a leftParanthese symbol
		cerr << "paranthese dismatch\n";
		return false;
	}

	//if the operation is a leftParanthese we push it in the stack no mather what
	if (currentOperation.symbol == leftParenthese)
	{
		operationStack.push(currentOperation);
		return true;
	}

	//the operation is neither leftParanthese nor rightParanthese

	while (!operationStack.isEmpty())
	{
		lastOperationAdded = operationStack.peek();

		if (
			(lastOperationAdded.priority > currentOperation.priority)
			||
			(lastOperationAdded.priority == currentOperation.priority
			&& lastOperationAdded.associativity == FROM_LEFT_TO_RIGHT)
			)
		{
			if (lastOperationAdded.symbol == leftParenthese)
			{
				break;
			}
			else
			{
				operationStack.pop();
				regularExpressionInPostfixNotation.push(lastOperationAdded.symbol);
			}
		}
		else //lastOperationAdded doesn't have a higher priority tha currentOperation
		{
			break;
		}
	}

	operationStack.push(currentOperation);
	return true;
}

bool convertTheRegularExpressionIntoPostfixNotation
(const char *regularExpressionString
, Stack<OperationOrSimpleRegularExpression> &regularExpressionInPostfixNotation)
{
	//We'll apply the shunting yard algorithm

	//the two main components are the stack with the operations
	//and the stack which elements make a valid postfix regular expressions

	Stack<Operation> operationStack;

	int pos = 0;
	
	//current symbol in the regular expression
	char currentSymbol;

	//result after adding an operation to the operation stack;
	//Example: we want th add rightParanthese in the stack,
	//but there is no leftParanthese in it, so the result is false
	//because there is a paranthese dismatch.
	bool result;

	//while we haven't yet read all the symbols in the regular expression
	while ( (currentSymbol = regularExpressionString[pos]) != '\0')
	{
		//if the symbol is an operation
		if (isInTheListOfOperations(currentSymbol))
		{
			result = addOperationToListOfOperations
				(getIndexOfOperationInListOfOperations(currentSymbol)
				, operationStack
				, regularExpressionInPostfixNotation);
			
			if (result == false)
			{
				return false;
			}
		}
		else
		{
			if (currentSymbol == initialSymbolOfSpecialString)
			{
				int indexOfSpecialString = getIndexOfSpecialStringPrefix
					(&regularExpressionString[pos]);

				assert(indexOfSpecialString != -1);

				regularExpressionInPostfixNotation.push(listOfSpecialStrings[indexOfSpecialString]);

				//we skip all the symbols that the special string consists of
				pos += strlen(listOfSpecialStrings[indexOfSpecialString]);
				
				continue;
			}
			else
			{
				//currentSymbol is neither an operation symbol
				//nor the initialSymbolForSpecialStrings
				regularExpressionInPostfixNotation.push(currentSymbol);
			}
		}

		//prepare for the reading of the next symbol in the
		//regular expresion
		++pos;
	}

	//this variable will store the operation ot top of the operationStack
	//until we extract all elements from it;
	Operation operationBuffer;

	//pop all remaining operations in operationStack and
	//add them to the regular expression
	while (!operationStack.isEmpty())
	{
		operationBuffer = operationStack.pop();
		
		if (operationBuffer.symbol == leftParenthese)
		{
			cerr << "parantheses dismatch\n";
			return false;
		}

		regularExpressionInPostfixNotation.push(operationBuffer.symbol);
	}

	//the regular expression is now fully in the stack
	//The only problem is that it's elements are in the oposite order 
	//we want them to be. We'll change that using a temporary stack.

	Stack<OperationOrSimpleRegularExpression> tempStack;

	while (!regularExpressionInPostfixNotation.isEmpty())
	{
		tempStack.push(regularExpressionInPostfixNotation.pop());
	}

	regularExpressionInPostfixNotation = tempStack;


	/*//remove the commment symbols, if you want to see the postfix expression

	while (!tempStack.isEmpty())
	{
		cout << tempStack.pop().notation;
	}
	cout << endl;
	*/

	return true;
}

