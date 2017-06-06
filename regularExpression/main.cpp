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


//if nameOfFileOrDirectory is valid and
//initialRegularExpression is a valid regular expression
//the function scans through all the files in the directory
//and prints out the lines, that correspond to the regular expression;
//else prints out an error mesage and returns false
bool scanTheFileOrDirectoryForTheRegularExpression
(const char *nameOfFileOrDirectory, const char *initialRegularExpressionString);



int main(int argc, char *argv[])
{
	//the program should receive two additional command line arguments
	if (argc < 3)
	{
		std::cerr << "not enough command line arguments\n";
		return 1;
	}

	//argv[1] is the name of the file or directory
	//argv[2] is the regular expression
	scanTheFileOrDirectoryForTheRegularExpression(argv[1], argv[2]);
	
	return  1;
}