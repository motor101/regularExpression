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

#ifndef OPERATION_H
#define OPERATION_H

#define FROM_LEFT_TO_RIGHT false
#define FROM_RIGHT_TO_LEFT true

struct Operation
{
	int priority;
	char symbol;
	bool associativity;
};

extern const int numberOfOperations;

extern const Operation listOfOperations[];

//returns false if symbol isn't a symbol of an operation in the list 
//of operations;
//else returns true
bool isInTheListOfOperations(char symbol);

//returns -1 if symbol isn't a symbol of an operation in the list 
//of operations;
//else returns the index of the operation in the list of operations
int getIndexOfOperationInListOfOperations(char symbol);

#endif //OPERATION_H