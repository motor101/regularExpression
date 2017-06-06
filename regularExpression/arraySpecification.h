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

#ifndef ARRAY_SPECIFICATION_H
#define ARRAY_SPECIFICATION_H

#include <stdexcept>

namespace fmi
{
namespace sdp
{

template <int size>
class Array
{
public:
	Array();

	Array(const Array<size> &other);

	Array<size>& operator=(const Array<size> &other);

	int& operator[](int index);

	int operator[](int index)const;

private:
	int arr[size];
};

#include "arrayRealization.hpp"

}	//sdp
}	//fmi

#endif //ARRAY_SPECIFICATION_H