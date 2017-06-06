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

#include <iostream>
#include <fstream>
#include "stringSpecification.h"
#include "stackSpecification.h"
#include "vectorSpecification.h"
#include "deterministicAutomaton.h"
#include "specialConstantsDeclarations.h"
#include "setSpecification.h"
#include "arraySpecification.h"


using namespace std;
using namespace fmi::sdp;
using namespace specialConstants;

static void printStringInfo(const char *nameOfString, const String &str);

//testing the methods of class String
void stringTest();

template <typename T>
void printStackInfo(const char *nameOfStack, const Stack<T> &myStack);

//tests the methods of class Stack<T>
void stackTest();

template <typename T>
static void printVectorInfo(const char *nameOfVector, const Vector<T>& myVector);

void vectorTest();

static void printAutomatonInfo(const DeterministicAutomaton& automaton, const char *nameOfAutomaton);

void testAutomaton();

static void printSetInfo(const Set &mySet, const char *nameOfSet);

void testSet();







static void printStringInfo(const char *nameOfString, const String &str)
{
	cout << nameOfString << ":\n"
		<< str << endl
		<< "c_str = " << str.c_str() << endl
		<< "size = " << str.getSize() << endl
		<< "capacity = " << str.getCapacity() << "\n\n";
}

//testing the methods of class String
void stringTest()
{
	String string1("hello");
	printStringInfo("string1", string1);

	string1 += " there";
	printStringInfo("string1", string1);

	String string2;
	printStringInfo("string2", string2);

	cout << "string2 = string1\n\n";
	string2 = string1;
	printStringInfo("string2", string2);

	string1 += string2;

	printStringInfo("string1", string1);

	String string3(string2);
	printStringInfo("string3", string3);

	string1 = "1234";

	cout << string1 + " " + string3 << endl;

}

template <typename T>
void printStackInfo(const char *nameOfStack, const Stack<T> &myStack)
{
	cout << nameOfStack<<":\n"
		<< nameOfStack << " is " << (myStack.isFull() ? "" : "not") << " full\n"
		<< nameOfStack << " is " << (myStack.isEmpty() ? "" : "not") << " empty\n"
		<< "size = " << myStack.getSize() << '\n'
		<< "capacity = " << myStack.getCapacity() << "\n\n";
}

//tests the methods of class Stack<T>
void stackTest()
{
	Stack<int> stack1;

	printStackInfo("stack1", stack1);
	
	for (int i = 0; i < stack1.getCapacity(); ++i)
		stack1.push(i);

	printStackInfo("stack1", stack1);

	//copy ctor
	Stack<int> stack2(stack1);

	printStackInfo("stack2", stack2);

	cout << "elements of stack2:\n";
	while (!stack2.isEmpty())
	{
		cout << stack2.pop() << ' ';
	}
	cout << "\n\n";

	printStackInfo("stack2", stack2);

	//operator=
	stack2 = stack1;

	printStackInfo("stack2", stack2);

	while (!stack2.isEmpty())
	{
		cout << stack2.pop() << ' ';
	}
	cout << "\n\n";

	printStackInfo("stack2", stack2);

	for (int i = 0; i < 100; ++i)
		stack2.push(i);

	printStackInfo("stack2", stack2);

}

template <typename T>
static void printVectorInfo(const char *nameOfVector, const Vector<T>& myVector)
{
	cout << nameOfVector << ":\n";
	for (int i = 0; i < myVector.getSize(); ++i)
		cout << myVector[i] << ' ';
	cout << '\n';
	cout << "size = " << myVector.getSize() << '\n'
		<< "capacity = " << myVector.getCapacity() << "\n\n";
}

void vectorTest()
{
	Vector<int> vector1;

	printVectorInfo("vector1", vector1);


	//testing push_back
	for (int i = 0; i < 10; ++i)
		vector1.push_back(i);

	printVectorInfo("vector1", vector1);

	for (int i = 0; i < 15; ++i)
		vector1.push_back(i);

	printVectorInfo("vector1", vector1);

	//testing operator[]
	for (int i = 0; i < 10; ++i)
		vector1[i] = 0;

	printVectorInfo("vector1", vector1);


	//testing copy ctor
	Vector<int> vector2(vector1);

	printVectorInfo("vector2", vector2);

	cout << "vector2.resize()\n\n";
	vector2.resize(50);

	printVectorInfo("vector2", vector2);


	cout << "vector2.clear()\n\n";
	vector2.clear();

	printVectorInfo("vector2", vector2);

	for (int i = 0; i < 5; ++i)
		vector2.push_back(i);

	//tetsing operator=
	
	cout<<"vector1 = vector2\n\n";
	vector1 = vector2;

	printVectorInfo("vector1", vector1);

	try
	{
		vector2[vector2.getCapacity()] = 2;
		cerr << "operator[] doesn't make index validation\n";
	}
	catch (std::invalid_argument& except)
	{
		cout << except.what() << endl;
	}


	const Vector<int> vector3 = vector1;

	//testing operator[]const
	cout << "vector3[0] = " << vector3[0] << endl;
}

static void printAutomatonInfo(const DeterministicAutomaton& automaton, const char *nameOfAutomaton)
{
	cout << nameOfAutomaton << ":\n";
	cout << "number of states = " << automaton.getNumberOfStates() << '\n'
		<< "number of final states = " << automaton.getNumberOfFinalStates() << "\n\n";
}

void testAutomaton()
{
	/*for (char symbol = firstValidSymbolInTheRegularExpression;
		symbol <= lastValidSymbolInTheRegularExpression; ++symbol)
	{
		cout << (int)symbol << ' ' << symbol << ' '
			<< DeterministicAutomaton::getIndexOfTheSymbolInTheTableOfTransitions(symbol) << endl;;
	}
	cout << "whitespace character " 
		<< DeterministicAutomaton::getIndexOfTheSymbolInTheTableOfTransitions('\t') << endl;
		*/

	
	DeterministicAutomaton automaton1("\\a");
	DeterministicAutomaton automaton2("\\d");

	DeterministicAutomaton automaton3 = DeterministicAutomaton::makeClosure(automaton1);

	DeterministicAutomaton automaton4 = DeterministicAutomaton::makeClosure(automaton2);

	DeterministicAutomaton automaton5 = DeterministicAutomaton::makeConcatenation(automaton3, automaton4);

	automaton4 = DeterministicAutomaton::makeUnion(automaton4,automaton1);

	printAutomatonInfo(automaton1, "automaton1");

	printAutomatonInfo(automaton2, "automaton2");

	printAutomatonInfo(automaton3, "automaton3");

	printAutomatonInfo(automaton4, "automaton4");

	printAutomatonInfo(automaton5, "automaton5");

	const char *nameOfFile = "textFile.txt";

	ifstream inputFile(nameOfFile);

	if (!inputFile)
	{
		cerr << "could not open " << nameOfFile << " for reading\n";
		return;
	}

	automaton5.scanTextFile(inputFile, nameOfFile);
	
}

static void printSetInfo(const Set &mySet, const char *nameOfSet)
{
	cout << nameOfSet << ":\n";
	
	int numberOfElements = 0;
	Set::Const_Iterator it = mySet.beginConst_Iterator();

	while (it != mySet.endConst_Iterator())
	{
		cout << *it << ' ';
		++numberOfElements;
		++it;
	}
	cout << '\n'
		<< "number of elements = " << numberOfElements << endl;
}

void testSet()
{
	Set set1;

	printSetInfo(set1, "set1");

	for (int i = 0; i < 10; ++i)
		set1.insert(i);

	set1.insert(3);
	set1.insert(1);
	set1.insert(-1);
	set1.insert(10);
	set1.insert(20);
	set1.insert(15);

	printSetInfo(set1, "set1");

	Set set2(set1);

	printSetInfo(set2, "set2");

	cout << "set1 " << ((set1 == set2) ? "=" : "!=" )<< " set2\n";

	set2.clear();
	printSetInfo(set2, "set2");

	set2.insert(4);
	set2 = set1;

	cout << "assigning set1 to set2:\n";
	cout << "set1 " << ((set1 == set2) ? "=" : "!=") << " set2\n";
	
	set2.clear();

	cout << "set1 " << ((set1 == set2) ? "=" : "!=") << " set2\n";

	set1.clear();

	cout << "set1 " << ((set1 == set2) ? "=" : "!=") << " set2\n";

	set1.insert(100);

	cout << "set1 " << ((set1 == set2) ? "=" : "!=") << " set2\n";

	set2.insert(100);

	cout << "set1 " << ((set1 == set2) ? "=" : "!=") << " set2\n";


}

