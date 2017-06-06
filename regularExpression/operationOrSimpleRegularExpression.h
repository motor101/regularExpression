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

#ifndef OPERATION_OR_SIMPLE_REGULAR_EXPRESSION
#define OPERATION_OR_SIMPLE_REGULAR_EXPRESSION

#include "specialConstantsDeclarations.h"

#define TYPE_IS_OPERATION false
#define TYPE_IS_SIMPLE_REG_EX true

class OperationOrSimpleRegularExpression
{
public:
	OperationOrSimpleRegularExpression(char symbol);

	OperationOrSimpleRegularExpression(const char *notation = specialConstants::emptyWord);

	OperationOrSimpleRegularExpression
		(const OperationOrSimpleRegularExpression &other);

	OperationOrSimpleRegularExpression& operator=
		(const OperationOrSimpleRegularExpression &other);

	~OperationOrSimpleRegularExpression();

	char *notation;

	bool type;
};


#endif //OPERATION_OR_SIMPLE_REGULAR_EXPRESSION