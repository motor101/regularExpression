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

#include <cassert>
#include <iostream>
#include "setSpecification.h"

using namespace fmi::sdp;

Set::Set()
:begin(NULL)
{}

Set::Set(const Set &other)
: begin(NULL)
{
	copy(begin, other.begin);
}

Set& Set::operator=(const Set &other)
{
	if (this != &other)
	{
		Node *newBegin = NULL;

		copy(newBegin, other.begin);

		clear();

		begin = newBegin;
	}
	return *this;
}

Set::~Set()
{
	clear();
}

//if newValue isn't in the set,
//adds it to the set and returns true;
//else returns false
bool Set::insert(int newValue)
{
	if (begin == NULL)
	{
		begin = new Node(newValue, NULL);
		return true;
	}

	Node *current = begin;
	Node *previous = begin;

	/*
		We will use the property of the structure of the set that:
		begin->value < begin->next->value < begin->next->next->value and so on...
	*/

	while (current != NULL)
	{
		if (newValue < current->value)
		{
			current->next = new Node(current->value, current->next);
			
			current->value = newValue;
			
			return true;
		}
		else
		{
			//if the value is already in the set we must not insert it
			if (newValue == current->value)
			{
				return false;
			}
			else //newValue > current->value
			{
				previous = current;
			
				current = current->next;
			}
		}
	}

	//previous is now pointing to the last element in the set
	previous->next = new Node(newValue, NULL);

	return true;
}

bool Set::operator==(const Set &other)const
{
	Node *current1 = begin;
	Node *current2 = other.begin;

	while (current1 != NULL && current2 != NULL)
	{
		if (current1->value != current2->value)
		{
			return false;
		}
		else
		{
			current1 = current1->next;
			current2 = current2->next;
		}
	}

	if (current1 == NULL && current2 == NULL)
	{
		return true;
	}
	else
	{
		return false;
	}
}
	
bool Set::operator!=(const Set &other)const
{
	return !( (*this) == other );
}

//removes all elements from the set
void Set::clear()
{
	Node *current = begin;
	
	Node *next;

	//we ensure that begin isn't pointing to a deleted Node
	begin = NULL;
	
	while (current != NULL)
	{
		next = current->next;
		
		delete current;
		
		current = next;
	}
}


//copies the set, starting from sourceBegin into a new set, starting
//from destinationBegin
void Set::copy(Node *&destinationBegin, const Node *sourceBegin)
{
	//if the source set is empty
	if (sourceBegin == NULL)
	{
		destinationBegin = NULL;
		return;
	}

	//the source set isn't empty

	//destinationBegin is passed by refference, so we must
	//ensure that its value is updated
	destinationBegin = new Node(sourceBegin->value, NULL);

	//Now we don't need destinationBegin any more
	//We only need it's value
	Node *destinationCurrent = destinationBegin;

	const Node *sourceCurrent = sourceBegin;

	//while we haven't reached the end of the source set
	while (sourceCurrent->next != NULL)
	{
		destinationCurrent->next = new Node(sourceCurrent->next->value, NULL);
		
		destinationCurrent = destinationCurrent->next;
		
		sourceCurrent = sourceCurrent->next;
	}
}