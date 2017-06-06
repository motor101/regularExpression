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

#ifndef SET_SPECIFICATION_H
#define SET_SPECIFICATION_H

#include <cstddef>

namespace fmi
{
namespace sdp
{
	
class Set
{
public:
	Set();

	Set(const Set &other);

	Set& operator=(const Set &other);

	~Set();

public:
	//if newValue isn't in the set,
	//adds newValue to the set and returns true;
	//else returns false
	bool insert(int newValue);

	bool operator==(const Set &other)const;

	bool operator!=(const Set &other)const;

	//removes all elements from the set
	void clear();

private:

	struct Node
	{
		Node(int value, Node *next = NULL)
		: value(value)
		, next(next)
		{}

		Node *next;
		int value;
	};
	
	//copies the set, starting from sourceBegin into a new set, starting
	//from destinationBegin
	static void copy(Node *&destinationBegin, const Node *sourceBegin);

public:
	class Const_Iterator
	{
		friend class Set;

	public:
		Const_Iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		Const_Iterator operator++(int)
		{
			Const_Iterator result(*this);
			
			++(*this);

			return result;
		}

		bool operator==(const Const_Iterator &other)const
		{
			return current == other.current;
		}

		bool operator!=(const Const_Iterator &other)const
		{
			return current != other.current;
		}

		//we shouldn't be able to change the elements in the set
		//using an iterator. That's why operator*() doesn't return
		//a reference!!!
		int operator*()const
		{
			return current->value;
		}

	private:
		Const_Iterator(Node *current)
			:current(current)
		{}

		Node *current;
	};

	Const_Iterator beginConst_Iterator()const
	{
		return Const_Iterator(begin);
	}

	Const_Iterator endConst_Iterator()const
	{
		return Const_Iterator(NULL);
	}

private:
	Node *begin;

};

}	//sdp
}	//fmi

#endif //SET_SPECIFICATION_H