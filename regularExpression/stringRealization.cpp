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

#include<iostream>
#include<stdexcept>		//invalid_argument
#include<cstring>
#include "stringSpecification.h"

using namespace std;

namespace fmi
{
namespace sdp
{
	//creates a String object with the required capacity
	//requiredCapacity must be a positive number
	String::String(int requiredCapacity)
	{
		if (requiredCapacity <= 0)
			throw invalid_argument("invalid capacity");

		capacity = requiredCapacity;

		arr = new char[capacity];

		//the initial size of the String must be 0
		arr[0] = '\0';
	}

	String::String(const String &other)
	{
		capacity = (other.capacity > defaultCapacity) ? other.capacity : defaultCapacity;

		arr = new char[capacity];

		strcpy(arr, other.arr);
	}

	String& String::operator=(const String &other)
	{
		if (this != &other)
		{
			int requiredCapacity = (other.capacity > defaultCapacity) ? other.capacity : defaultCapacity;

			char *newArr = new char[requiredCapacity];

			strcpy(newArr, other.arr);

			clear();

			arr = newArr;

			capacity = requiredCapacity;
		}
		return *this;
	}

	String::~String()
	{
		clear();
	}

	//charArray must be a '\0' terminated string
	String::String(const char *charArray)
	{
		int requiredCapacity = strlen(charArray) + 1;

		capacity = (requiredCapacity > defaultCapacity) ? requiredCapacity : defaultCapacity;

		arr = new char[capacity];

		strcpy(arr, charArray);
	}

	String& String::operator+=(const String &other)
	{
		int size1 = strlen(arr);

		int size2 = strlen(other.arr);

		//if the dynamically allocated memory is big enough to fit the new String
		if (size1 + size2 < capacity)
		{
			//append other.arr to arr
			strcpy( &arr[size1], other.arr);
		}

		else
		{
			//the new capacity will be twice as big as the capacity we need
			//in case we want to use the operator+= multiple times in the program
			int newCapacity = 2 * (size1 + size2 + 1);

			char *newArr = new char[newCapacity];

			strcpy(newArr, arr);

			//append other.arr to newArr
			strcpy( &newArr[size1], other.arr);

			clear();

			arr = newArr;

			capacity = newCapacity;
		}
		return *this;
	}

	///returns a c type string represenation of the current String
	const char* String::c_str() const
	{
		return arr;
	}

	unsigned int String::getSize() const
	{
		return strlen(arr);
	}

	int String::getCapacity() const
	{
		return capacity;
	}

	ostream& operator<< (ostream &out, const String &str)
	{
		out << str.arr;

		return out;
	}

	//deletes the dinamically allocated memory and makes capacity
	//and arr equal to 0
	void String::clear()
	{
		delete[] arr;

		arr = NULL;

		capacity = 0;
	}

	String operator+(const String &first, const String &second)
	{
		String result(first);

		result += second;

		return result;
	}

}	//sdp
}	//fmi
