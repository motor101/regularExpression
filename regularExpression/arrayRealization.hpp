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

template<int size>
inline Array<size>::Array()
{
	if (size <= 0)
		throw std::invalid_argument("invalid size");
}

template <int size>
inline Array<size>::Array(const Array<size> &other)
{
	for (int i = 0; i < size; ++i)
	{
		arr[i] = other.arr[i];
	}
}

template<int size>
inline Array<size>& Array<size>::operator=(const Array<size> &other)
{
	if (this != &other)
	{
		for (int i = 0; i < size; ++i)
		{
			arr[i] = other.arr[i];
		}
	}
	return *this;
}

template<int size>
inline int& Array<size>::operator[](int index)
{
	return arr[index];
}

template<int size>
inline int Array<size>::operator[](int index)const
{
	return arr[index];
}
