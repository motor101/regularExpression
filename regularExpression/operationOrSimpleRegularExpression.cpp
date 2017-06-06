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

#include <cstring>
#include "Operation.h"
#include "operationOrSimpleRegularExpression.h"

OperationOrSimpleRegularExpression::OperationOrSimpleRegularExpression(char symbol)
:notation(NULL)
{
	if (isInTheListOfOperations(symbol))
	{
		type = TYPE_IS_OPERATION;
	}
	else
	{
		type = TYPE_IS_SIMPLE_REG_EX;
	}
	
	notation = new char[2];
	notation[0] = symbol;
	notation[1] = '\0';
}


OperationOrSimpleRegularExpression::OperationOrSimpleRegularExpression
(const char *notation)
:notation(NULL)
{
	//if the type was an operation, then the argument would have been a symbol
	//since the argument is a string, the type is a simple regular expression
	type = TYPE_IS_SIMPLE_REG_EX;

	this->notation = new char[strlen(notation) + 1];

	strcpy(this->notation, notation);
}

OperationOrSimpleRegularExpression::OperationOrSimpleRegularExpression
(const OperationOrSimpleRegularExpression &other)
:notation(NULL)
{
	notation = new char[strlen(other.notation) + 1];

	strcpy(notation, other.notation);

	type = other.type;
}

OperationOrSimpleRegularExpression& OperationOrSimpleRegularExpression::operator=
(const OperationOrSimpleRegularExpression &other)
{
	if (this != &other)
	{
		delete[] notation;

		notation = new char[strlen(other.notation) + 1];

		strcpy(notation, other.notation);

		type = other.type;
	}

	return *this;
}

OperationOrSimpleRegularExpression::~OperationOrSimpleRegularExpression()
{
	delete[] notation;
}