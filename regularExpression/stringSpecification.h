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

#ifndef STRING_SPECIFICATION_H
#define STRING_SPECIFICATION_H

#include<iostream>

namespace fmi
{
namespace sdp
{

	class String
	{
	public:
		//creates a String object with the required capacity
		//requiredCapacity must be a positive number
		String(int requiredCapacity = defaultCapacity);

		String(const String &other);

		String& operator=(const String &other);

		~String();

	public:
		//charArray must be a '\0' terminated string
		String(const char *charArray);

		//appends the content of other to the String
		String& operator+=(const String &other);

	public:
		///returns a c type string represenation of the current String
		const char* c_str()const;

		unsigned int getSize()const;

		int getCapacity()const;

		friend std::ostream& operator<<(std::ostream &out, const String &str);

	protected:
		//deletes the dynamically allocated memory and makes capacity
		//and arr equal to 0
		void clear();

	private:
		char *arr;

		int capacity;

		static const int defaultCapacity=10;
	};
	
	String operator+(const String &first, const String &second);

}	//sdp
}	//fmi

#endif //STRING_SPECIFICATION_H