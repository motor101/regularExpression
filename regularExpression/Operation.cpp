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

#include"Operation.h"
#include "specialConstantsDeclarations.h"

using namespace specialConstants;

extern const int numberOfOperations = 5;

extern const Operation listOfOperations[numberOfOperations]
{
	  { 10, leftParenthese, FROM_LEFT_TO_RIGHT}
	, { 10, rightParenthese, FROM_LEFT_TO_RIGHT }
	, { 3, symbolForClosure, FROM_LEFT_TO_RIGHT }
	, { 2, symbolForConcatenation, FROM_LEFT_TO_RIGHT }
	, { 1, symbolForUnion, FROM_LEFT_TO_RIGHT }
}; 

//returns false if symbol isn't a symbol of an operation in the list 
//of operations;
//else returns true
bool isInTheListOfOperations(char symbol)
{
	return getIndexOfOperationInListOfOperations(symbol) != -1;
}

//returns -1 if symbol isn't a symbol of an operation in the list 
//of operations;
//else returns the index of the operation in the list of operations
int getIndexOfOperationInListOfOperations(char symbol)
{
	for (int i = 0; i < numberOfOperations; ++i)
	{
		if (listOfOperations[i].symbol == symbol)
		{
			return i;
		}
	}

	return -1;
}