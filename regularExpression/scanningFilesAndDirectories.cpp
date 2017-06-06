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

#include <fstream>
#include <dirent.h>
#include <sys/types.h>
#include "deterministicAutomaton.h"
#include "stringSpecification.h"

using namespace std;
using namespace fmi::sdp;

//if nameOfFileOrDirectory is a name of file,
//then the automaton scans the file;
//else if nameOfFileOrDirectory is a name of a directory,
//then the automaton scans all files in the firectory
//including the files in the subdirectories;
//else prints out an error message
void scanningFilesWithDeterministicAutomaton
(const String &nameOfFileOrDirectory, const DeterministicAutomaton &automaton)
{
	//by this point we don't know if the string argument is a name of
	//a file or a directory
	
	//firstly we'll try to open it as a file
	
	ifstream inputFile(nameOfFileOrDirectory.c_str());
	
	if (inputFile.is_open())
	{
		automaton.scanTextFile(inputFile, nameOfFileOrDirectory.c_str());
		inputFile.close();
		return;
	}
	else
	{
		DIR *dir = opendir(nameOfFileOrDirectory.c_str());
		
		//if the string is a name of a directory
		if (dir)
		{
			dirent *direntPointer;

			//the first two objects in every Windows directory
			//are the current directory and the father directory
			//we don't want to scan them!!!
			//that's why we need a counter to skip them
			int counter = 0;
			
			//while we have't reached the end of the directory
			while ( (direntPointer = readdir(dir) ) != NULL)
			{
				if (counter == 0 || counter == 1)
				{
					++counter;
					continue;
				}
	
				//we're goint to scan all the files in this subdirectory
				scanningFilesWithDeterministicAutomaton
					( nameOfFileOrDirectory + "\\" + direntPointer->d_name
					, automaton );
			}
			closedir(dir);
		}
		else
		{
			cerr << nameOfFileOrDirectory.c_str()
				<< " couldn't be opened neither as an input file"
				" nor as a directory\n";
		}
	}
}
