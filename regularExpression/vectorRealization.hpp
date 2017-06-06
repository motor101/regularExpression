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

#ifndef VECTOR_REALIZATION_HPP
#define VECTOR_REALIZATION_HPP

//requiredCapacity must be a positive number
template<typename T>
inline Vector<T>::Vector(int requiredCapacity)
	: capacity(requiredCapacity)
	, size(0)
	, arr(NULL)
{
	if (capacity <= 0)
	{
		throw std::invalid_argument("the capacity of the Vector must be a positive number");
	}

	arr = new T[capacity];
}

template<typename T>
inline Vector<T>::Vector(const Vector &other)
	: capacity(other.capacity)
	, size(other.size)
	, arr(NULL)
{
	capacity = (capacity > defaultCapacity) ? capacity : defaultCapacity;
	
	arr = new T[capacity];

	for (int i = 0; i < size; ++i)
	{
		arr[i] = other.arr[i];
	}

}

template<typename T>
inline Vector<T>& Vector<T>::operator=(const Vector &other)
{
	if (this != &other)
	{
		int newCapacity = (other.capacity > defaultCapacity) ? other.capacity : defaultCapacity;

		T *newArr = new T[newCapacity];

		for (int i = 0; i < other.size; ++i)
		{
			newArr[i] = other.arr[i];
		}

		clear();

		arr = newArr;
		size = other.size;
		capacity = newCapacity;
	}

	return *this;
}

template<typename T>
inline Vector<T>::~Vector()
{
	clear();
}

//adds element at the end of the Vector
template<typename T>
inline void Vector<T>::push_back(const T &element)
{
	if (size == capacity)
	{
		//ensure that there is enough space for
		//one more element
		reserve(size + 1);
	}

	arr[size++] = element;
}

//throws exception, if the index is invalid
//index must be in the interval [0; size)
template<typename T>
inline T& Vector<T>::operator[](int index)
{
	if (index < 0 || index >= size)
	{
		throw std::invalid_argument("invalid index");
	}
	
	return arr[index];
}

//throws exception, if the index is invalid
//index must be in the interval [0; size)
template<typename T>
inline const T& Vector<T>::operator[](int index)const
{
	if (index < 0 || index >= size)
	{
		throw std::invalid_argument("invalid index");
	}

	return arr[index];
}

//makes the size of the Vector equal to requiredSize
template<typename T>
inline void Vector<T>::resize(int requiredSize)
{
	if (requiredSize < 0)
	{
		throw std::invalid_argument("invalid size");
	}

	reserve(requiredSize);

	size = requiredSize;
}

//ensures that the capacity of the Vector is at least 
//equal to requiredCapacity
template<typename T>
inline void Vector<T>::reserve(int requiredCapacity)
{
	if (capacity < requiredCapacity)
	{
		int newCapacity = (requiredCapacity > 2 * capacity) ? requiredCapacity : 2 * capacity;

		T *newArr = new T[newCapacity];

		for (int i = 0; i < size; ++i)
		{
			newArr[i] = arr[i];
		}

		//here we must not use the function clear()
		//because it makes size equal to 0
		delete[] arr;
		
		arr = newArr;

		capacity = newCapacity;
	}
}

//frees the dynamically allocated memory for the Vector
//and makes the size and the capacity equal to 0
template<typename T>
inline void Vector<T>::clear()
{
	delete[] arr;
	arr = NULL;

	capacity = size = 0;
}

#endif //VECTOR_REALIZATION_HPP