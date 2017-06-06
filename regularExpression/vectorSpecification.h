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

#ifndef VECTOR_SPECIFICATION_H
#define VECTOR_SPECIFICATION_H

#include<stdexcept>

namespace fmi
{
namespace sdp
{
	template<typename T>
	class Vector
	{
	public:
		//requiredCapacity must be a positive number
		Vector(int requiredCapacity = defaultCapacity);
		
		Vector(const Vector &other);
		
		Vector<T>& operator=(const Vector &other);
		
		~Vector();

	public:
		//adds element at the end of the Vector
		void push_back(const T &element);

		//throws exception, if the index is invalid
		//index must be in the interval [0; size)
		T& operator[](int index);

		//throws exception, if the index is invalid
		//index must be in the interval [0; size)
		const T& operator[](int index)const;

	public:
		int getSize()const 
		{
			return size;
		}

		int getCapacity()const 
		{
			return capacity;
		}

		//makes the size of the Vector equal to requiredSize
		void resize(int requiredSize);

		//ensures that the capacity of the Vector is at least 
		//equal to requiredCapacity
		void reserve(int requiredCapacity);

		//frees the dynamically allocated memory for the Vector
		//and makes the size and the capacity equal to 0
		void clear();

	private:
		T *arr;
		int size;
		int capacity;

		static const int defaultCapacity = 10;
	};

#include "vectorRealization.hpp"

}	//sdp
}	//fmi


#endif //VECTOR_SPECIFICATION_H