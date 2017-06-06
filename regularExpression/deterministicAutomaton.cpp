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
#include <cstring>
#include <cassert>
#include <cctype>
#include "deterministicAutomaton.h"
#include "vectorSpecification.h"
#include "setSpecification.h"


using namespace fmi::sdp;
using namespace specialConstants;
using namespace std;

//constructs a deterministic automaton, which can recognize simpleRegularExpression;
//simpleRegularExpression must be "", or a string with one letter or a special string
//special strings start with initialSymbolForSpecialStrings and are elements of
//the list of special strings
DeterministicAutomaton::DeterministicAutomaton(const char *simpleRegularExpression)
{
	int lengthOfExpression = strlen(simpleRegularExpression);
	
	//if the expression is the empty string "",
	//then the automaton will have only one state,
	//which is at the same time initial and final state.
	//Every transition From that state will go To that state!
	if (lengthOfExpression == 0)
	{
		tableOfTransitions.resize(1);

		//the table of final states will have one final state - the initial state
		orderedListOfFinalStates.push_back(indexOfInitialState);

		//fill in the table of transitions
		makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
			(indexOfInitialState, 0, numberOfElementsInTheTableOfTransitions - 1, indexOfInitialState);	
	}
	else //lengthOfExpression >= 1
	{
		char firstSymbol = simpleRegularExpression[0];

		//if the expression isn't valid
		if (

			(lengthOfExpression == 1 && !isInTheAlphabetOfTheAutomaton(firstSymbol) )
			||
			(
			lengthOfExpression > 1 &&
			(firstSymbol != initialSymbolOfSpecialString || !isSpecialString(simpleRegularExpression) )
			)

			)
		{
			throw invalid_argument("the string is not a simple regular expression");
		}

		
		//if the expression is emptyWord, then the automaton will have only
		//two states: one initial state which is at the same time final
		//and one non-final state with no escape
		if (strcmp(simpleRegularExpression, emptyWord) == 0)
		{
			tableOfTransitions.resize(2);

			const int indexOfStateWithNoEscape = indexOfInitialState + 1;

			orderedListOfFinalStates.push_back(indexOfInitialState);

			//make all transitions in the row of the initial state 
			//go to the non-final state with no escape
			makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
				(indexOfInitialState, 0, numberOfElementsInTheTableOfTransitions - 1, indexOfStateWithNoEscape);

			//make all transitions in the row of the state with no escape 
			//go to the same state
			makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
				(indexOfStateWithNoEscape, 0, numberOfElementsInTheTableOfTransitions - 1, indexOfStateWithNoEscape);
		}
		else
		{
			//in all other cases the states of the automaton will be 3: 
			//one initial state, which isn't final
			//one final state and
			//one non-final state with no escape

			tableOfTransitions.resize(3);

			const int indexOfFinalState = indexOfInitialState + 1;
			const int indexOfStateWithNoEscape = indexOfFinalState + 1;

			orderedListOfFinalStates.push_back(indexOfFinalState);

			makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
				(indexOfInitialState, 0, numberOfElementsInTheTableOfTransitions - 1, indexOfStateWithNoEscape);

			makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
				(indexOfFinalState, 0, numberOfElementsInTheTableOfTransitions - 1, indexOfStateWithNoEscape);

			makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
				(indexOfStateWithNoEscape, 0, numberOfElementsInTheTableOfTransitions - 1, indexOfStateWithNoEscape);

			if (lengthOfExpression == 1)
			{
				tableOfTransitions[indexOfInitialState]
					[getIndexOfTheSymbolInTheTableOfTransitions(firstSymbol)] = indexOfFinalState;
			}
			else if (strcmp(simpleRegularExpression, backSlash) == 0)
			{
				tableOfTransitions[indexOfInitialState]
					[getIndexOfTheSymbolInTheTableOfTransitions('\\')] = indexOfFinalState;
			}
			else if (strcmp(simpleRegularExpression, randomWhiteCharacter) == 0)
			{
				tableOfTransitions[indexOfInitialState]
					[getIndexOfTheSymbolInTheTableOfTransitions('\t')] = indexOfFinalState;
			}
			else if (strcmp(simpleRegularExpression, randomDigit) == 0)
			{
				makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
					(indexOfInitialState, getIndexOfTheSymbolInTheTableOfTransitions('0')
					, getIndexOfTheSymbolInTheTableOfTransitions('9'), indexOfFinalState);
			}
			else if (strcmp(simpleRegularExpression, randomLetter) == 0)
			{
				makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
					(indexOfInitialState, getIndexOfTheSymbolInTheTableOfTransitions('A')
					, getIndexOfTheSymbolInTheTableOfTransitions('Z'), indexOfFinalState);
			}
			else
			{
				assert(false);
			}
		}
	}
}

//scans the input file line by line and prints out the lines that bring it to a final state
void DeterministicAutomaton::scanTextFile(std::ifstream &inputFile, const char *nameOfFile) const
{
	char symbol;

	int lineNumber = 0;

	int startingPositionOfLine = 0;

	int indexOfCurrentState = indexOfInitialState;

	bool theLineContainsAnInvalidSymbol = false;

	do
	{
		symbol = inputFile.get();

		//if the end of the line is reached
		if (symbol == '\n' || symbol == EOF)
		{
			//if the automaton recognizes the line
			if (isFinalState(indexOfCurrentState) && theLineContainsAnInvalidSymbol == false)
			{
				cout << nameOfFile << ':' << lineNumber << ':';

				inputFile.clear();

				inputFile.seekg(startingPositionOfLine, ios::beg);
				
				while ((symbol = inputFile.get() ) != '\n' && symbol != EOF)
				{
					cout << symbol;
				}
				cout << '\n';
			}

			//prepare the variables for reading a new line

			inputFile.clear();

			startingPositionOfLine = inputFile.tellg();

			indexOfCurrentState = indexOfInitialState;

			theLineContainsAnInvalidSymbol = false;

			++lineNumber;

		}
		else
		{
			if (isInTheAlphabetOfTheAutomaton(symbol) == false)
			{
				theLineContainsAnInvalidSymbol = true;
			}
			else
			{
				//the current state of the automaton changes, depending from the value of symbol
				indexOfCurrentState =
					tableOfTransitions[indexOfCurrentState][getIndexOfTheSymbolInTheTableOfTransitions(symbol)];
			}
		}

	} 
	while (symbol != EOF);

}

//returns the number of states of the automaton
int DeterministicAutomaton::getNumberOfStates() const
{
	return tableOfTransitions.getSize();
}


//returns the number of final states of the automaton
int DeterministicAutomaton::getNumberOfFinalStates() const
{
	return orderedListOfFinalStates.getSize();
}

DeterministicAutomaton DeterministicAutomaton::makeConcatenation
(const DeterministicAutomaton &automaton1, const DeterministicAutomaton &automaton2)
{
	DeterministicAutomaton result;

	result.tableOfTransitions.resize(0);
	result.orderedListOfFinalStates.resize(0);

	DeterministicAutomaton nonDeterministicAutomaton;

	nonDeterministicAutomaton.tableOfTransitions.resize(0);
	nonDeterministicAutomaton.orderedListOfFinalStates.resize(0);

	//firstly we'll fill in the list of final states of the Non-deterministic automaton

	//when performing concatenation, every state of automaton1 is considered non-final
	//for the non-denerministic automaton of concatenation
	nonDeterministicAutomaton.orderedListOfFinalStates
		.reserve(automaton2.getNumberOfFinalStates());

	//we'll use this constant to avoid collisions between the indexes of final
	//states in automaton1 and automaton2
	const int numberOfStatesInAutomaton1 = automaton1.getNumberOfStates();

	//push all final states of automaton2 into the list of final states
	//of nonDeterministicAutomaton
	for (int i = 0; i < automaton2.getNumberOfFinalStates(); ++i)
	{
		nonDeterministicAutomaton.orderedListOfFinalStates
			.push_back(automaton2.orderedListOfFinalStates[i] + numberOfStatesInAutomaton1);
	}

	//now we'll fill in the table of transitions of the Non-deterministic automaton


	//!!!we don't use reserve() here but resize()!!!
	//decause we won't PUSH the rows. We'll COPY them instead!
	nonDeterministicAutomaton.tableOfTransitions
		.resize(automaton1.getNumberOfStates() + automaton2.getNumberOfStates());


	//copy all rows from the table of transitions of automaton1 to the table of
	//transitions of the non-deterministic automaton
	for (int indexOfState = 0; indexOfState < automaton1.getNumberOfStates(); ++indexOfState)
	{
		for (int indexOfSymbol = 0;
			indexOfSymbol < numberOfElementsInTheTableOfTransitions;
			++indexOfSymbol)
		{
			nonDeterministicAutomaton.tableOfTransitions[indexOfState][indexOfSymbol]

				= automaton1.tableOfTransitions[indexOfState][indexOfSymbol];
		}
	}


	//copy all rows from the table of transitions of automaton2 to the table of
	//transitions of the non-deterministic automaton in such a way that no collisions
	//between the states of automaton1 and automaton2 occur
	for (int indexOfState = 0; indexOfState < automaton2.getNumberOfStates(); ++indexOfState)
	{
		for (int indexOfSymbol = 0;
			indexOfSymbol < numberOfElementsInTheTableOfTransitions; 
			++indexOfSymbol)
		{
			nonDeterministicAutomaton.tableOfTransitions[indexOfState + numberOfStatesInAutomaton1][indexOfSymbol]

				= automaton2.tableOfTransitions[indexOfState][indexOfSymbol] + numberOfStatesInAutomaton1;
		}
	}

	Set elementsInInitialState;

	//the determinating of the automaton starts from the initial state of
	//automaton1
	elementsInInitialState.insert(automaton1.indexOfInitialState);

	//if the initial state of automaton1 is also final,
	//then we have to add the initial state of automaton2
	//to the initial set of result
	if (automaton1.isFinalState(automaton1.indexOfInitialState))
	{
		elementsInInitialState.insert(automaton2.indexOfInitialState + numberOfStatesInAutomaton1);
	}

	//every new state will be stored in this list
	Vector<Set> listOfCreatedStates;

	constructConcatenationAutomaton
		( elementsInInitialState
		, nonDeterministicAutomaton
		, result
		, listOfCreatedStates
		, automaton1);


	return result;
}

DeterministicAutomaton DeterministicAutomaton::makeUnion
(const DeterministicAutomaton &automaton1, const DeterministicAutomaton &automaton2)
{
	DeterministicAutomaton result;

	result.tableOfTransitions.resize(0);
	result.orderedListOfFinalStates.resize(0);

	DeterministicAutomaton nonDeterministicAutomaton;

	nonDeterministicAutomaton.tableOfTransitions.resize(0);
	nonDeterministicAutomaton.orderedListOfFinalStates.resize(0);

	//firstly we'll fill in the list of final states of the Non-deterministic automaton

	//the final states of the non-deterministic automaton are the final states of
	//automaton1 and automaton2
	nonDeterministicAutomaton.orderedListOfFinalStates
		.reserve(automaton1.getNumberOfFinalStates() + automaton2.getNumberOfFinalStates() );

	//push all final states of automaton1 into the list of final states
	//of nonDeterministicAutomaton
	for (int i = 0; i < automaton1.getNumberOfFinalStates(); ++i)
	{
		nonDeterministicAutomaton.orderedListOfFinalStates
			.push_back(automaton1.orderedListOfFinalStates[i]);
	}

	//we'll use this constant to avoid collisions between the indexes of final
	//states in automaton1 and automaton2
	const int numberOfStatesInAutomaton1 = automaton1.getNumberOfStates();

	//push all final states of automaton2 into the list of final states
	//of nonDeterministicAutomaton
	for (int i = 0; i < automaton2.getNumberOfFinalStates(); ++i)
	{
		nonDeterministicAutomaton.orderedListOfFinalStates
			.push_back(automaton2.orderedListOfFinalStates[i] + numberOfStatesInAutomaton1);
	}

	//now we'll fill in the table of transitions of the Non-deterministic automaton


	//!!!we don't use reserve() here but resize()!!!
	//decause we won't PUSH the rows. We'll COPY them instead!
	nonDeterministicAutomaton.tableOfTransitions
		.resize(automaton1.getNumberOfStates() + automaton2.getNumberOfStates());


	//copy all rows from the table of transitions of automaton1 to the table of
	//transitions of the non-deterministic automaton
	for (int indexOfState = 0; indexOfState < automaton1.getNumberOfStates(); ++indexOfState)
	{
		for (int indexOfSymbol = 0;
			indexOfSymbol < numberOfElementsInTheTableOfTransitions; ++indexOfSymbol)
		{
			nonDeterministicAutomaton.tableOfTransitions[indexOfState][indexOfSymbol]

				= automaton1.tableOfTransitions[indexOfState][indexOfSymbol];
		}
	}


	//copy all rows from the table of transitions of automaton2 to the table of
	//transitions of the non-deterministic automaton
	for (int indexOfState = 0; indexOfState < automaton2.getNumberOfStates(); ++indexOfState)
	{
		for (int indexOfSymbol = 0;
			indexOfSymbol < numberOfElementsInTheTableOfTransitions; ++indexOfSymbol)
		{
			nonDeterministicAutomaton.tableOfTransitions[indexOfState + numberOfStatesInAutomaton1][indexOfSymbol]

				= automaton2.tableOfTransitions[indexOfState][indexOfSymbol] + numberOfStatesInAutomaton1;
		}
	}

	Set elementsInInitialState;
	
	//the initial state of the non-deterministic automaton consists of the
	//initial states of automatin1 and automaton2
	elementsInInitialState.insert(automaton1.indexOfInitialState);
	elementsInInitialState.insert(automaton2.indexOfInitialState + numberOfStatesInAutomaton1);

	//every new state will be stored in this list
	Vector<Set> listOfCreatedStates;

	constructUnionAutomaton
		(elementsInInitialState
		, nonDeterministicAutomaton
		, result
		, listOfCreatedStates);

	return result;
}

DeterministicAutomaton DeterministicAutomaton::makeClosure
(const DeterministicAutomaton &automatonThatWeWantoToClose)
{
	DeterministicAutomaton result;

	result.orderedListOfFinalStates.clear();
	result.tableOfTransitions.clear();

	Set elementsInInitialSet;

	elementsInInitialSet.insert(automatonThatWeWantoToClose.indexOfInitialState);

	//every new state will be stored in this list
	Vector<Set> listOfCreatedStates;

	constructClosureAutomaton
		(elementsInInitialSet
		, automatonThatWeWantoToClose
		, result
		, listOfCreatedStates);

	return result;
}

//represents the transforming of a non-deterministic automaton,
//which is a closure of a deterministic automaton - 
//automatonThatWeWantToClose, into a deterministic automaton - 
//result;
//listOfCreated represents the set of states which comprise
//the already created states
void DeterministicAutomaton::constructClosureAutomaton
( const Set &elementsInCurrentState
, const DeterministicAutomaton &automatonThatWeWantoToClose
, DeterministicAutomaton &result
, Vector<Set> &listOfCreatedStates)
{
	assert(listOfCreatedStates.getSize() == result.getNumberOfStates());

	const int indexOfCurrentState = listOfCreatedStates.getSize();

	listOfCreatedStates.push_back(elementsInCurrentState);

	//increase the size of the table of transitions by one row
	result.tableOfTransitions.resize(result.getNumberOfStates() + 1);

	//we'll use this iterator to traverse through all elements in the current set
	Set::Const_Iterator it = elementsInCurrentState.beginConst_Iterator();

	//if there is a final state in the list of states from which the current
	//state consists then the current state is also final
	for (it = elementsInCurrentState.beginConst_Iterator();
		it != elementsInCurrentState.endConst_Iterator();
		++it)
	{
		if (automatonThatWeWantoToClose.isFinalState(*it) 
			|| *it == automatonThatWeWantoToClose.indexOfInitialState)
		{
			//push the index of the current state to the list of final states
			result.orderedListOfFinalStates.push_back(indexOfCurrentState);
			break;
		}
	}

	Set elementsInTheNewState;


	//we want to find out the state that the automaton goes to from 
	//its current state, when it encounters a random symbol in it's alphabet
	for (int indexOfSymbol = 0;
		indexOfSymbol < numberOfElementsInTheTableOfTransitions;
		++indexOfSymbol)
	{
		for (it = elementsInCurrentState.beginConst_Iterator();
			it != elementsInCurrentState.endConst_Iterator();
			++it)
		{
			elementsInTheNewState.insert
				(automatonThatWeWantoToClose.tableOfTransitions[*it][indexOfSymbol]);
		}

		//it the new state has an element which is a final state
		//then the new state must also have the initial element of
		//the automaton
		for (it = elementsInTheNewState.beginConst_Iterator();
			it != elementsInTheNewState.endConst_Iterator();
			++it)
		{
			if (automatonThatWeWantoToClose.isFinalState(*it))
			{
				elementsInTheNewState.insert
					(automatonThatWeWantoToClose.indexOfInitialState);
				break;
			}
		}

		//now we know the indexes of the states which consist the new state

		int indexOfCreatedState;

		int indexOfNewState;

		//let's see if we have previously constructed a state with these elements;
		//we' ll scan through all created states to find out
		for (indexOfCreatedState = 0; indexOfCreatedState < listOfCreatedStates.getSize();
			++indexOfCreatedState)
		{
			if (elementsInTheNewState == listOfCreatedStates[indexOfCreatedState])
			{
				indexOfNewState = indexOfCreatedState;
				break;
			}
		}

		//if the state we have just constructed is a new state 
		//(isn't in the list of created states)
		if (indexOfCreatedState == listOfCreatedStates.getSize())
		{
			indexOfNewState = result.getNumberOfStates();

			constructClosureAutomaton
				( elementsInTheNewState
				, automatonThatWeWantoToClose
				, result
				, listOfCreatedStates);
		}
		elementsInTheNewState.clear();

		result.tableOfTransitions[indexOfCurrentState][indexOfSymbol] = indexOfNewState;
	}

}

//represents the transforming of a non-deterministic automaton,
//which is a union of two deterministic automatons, into a 
//deterministic automaton - result;
//listOfCreated represents the set of states which comprise
//the already created states
void DeterministicAutomaton::constructUnionAutomaton
	( const Set &elementsInCurrentState
	, const DeterministicAutomaton &nonDeterministicAutomaton
	, DeterministicAutomaton &result
	, Vector<Set> &listOfCreatedStates
	)
{
	assert(listOfCreatedStates.getSize() == result.getNumberOfStates() );

	const int indexOfCurrentState = listOfCreatedStates.getSize();

	
	listOfCreatedStates.push_back(elementsInCurrentState);

	//increase the size of the table of transitions by one row
	result.tableOfTransitions.resize(result.getNumberOfStates() + 1);

	//we'll use this iterator to traverse through all elements in the current set
	Set::Const_Iterator it = elementsInCurrentState.beginConst_Iterator();

	//if there is a final state in the list of states from which the current
	//state consists then the current state is also final
	for (it = elementsInCurrentState.beginConst_Iterator();
		 it != elementsInCurrentState.endConst_Iterator();
		 ++it)
	{
		if (nonDeterministicAutomaton.isFinalState(*it))
		{
			//push the index of the current state to the list of final states
			result.orderedListOfFinalStates.push_back(indexOfCurrentState);
			break;
		}
	}

	Set elementsInTheNewState;


	//we want to find out the state that the automaton goes to from 
	//its current state, when it encounters a random symbol in it's alphabet
	for (int indexOfSymbol = 0; 
		indexOfSymbol < numberOfElementsInTheTableOfTransitions; 
		++indexOfSymbol)
	{
		for (it = elementsInCurrentState.beginConst_Iterator();
			it != elementsInCurrentState.endConst_Iterator();
			++it)
		{
			elementsInTheNewState.insert
				(nonDeterministicAutomaton.tableOfTransitions[*it] [indexOfSymbol] );
		}

		//now we know the indexes of the states which consist the new state

		int indexOfCreatedState;

		int indexOfNewState;

		//let's see if we have previously constructed a state with these elements;
		//we' ll scan through all created states to find out
		for (indexOfCreatedState = 0; indexOfCreatedState < listOfCreatedStates.getSize();
			++indexOfCreatedState)
		{
			if (elementsInTheNewState == listOfCreatedStates[indexOfCreatedState])
			{
				indexOfNewState = indexOfCreatedState;
				break;
			}
		}

		//if the state we have just constructed is a new state 
		//(isn't in the list of created states)
		if (indexOfCreatedState == listOfCreatedStates.getSize())
		{
			indexOfNewState = result.getNumberOfStates();

			constructUnionAutomaton
				(elementsInTheNewState
				, nonDeterministicAutomaton
				, result
				, listOfCreatedStates
				);
		}
		elementsInTheNewState.clear();

		result.tableOfTransitions[indexOfCurrentState][indexOfSymbol] = indexOfNewState;
	}

}

//represents the transforming of a non-deterministic automaton,
//which is a concatenation of two deterministic automatons: automaton1
//and automaton2, into a 
//deterministic automaton - result;
//listOfCreated represents the set of states which comprise
//the already created states
void DeterministicAutomaton::constructConcatenationAutomaton
(const Set &elementsInCurrentState
, const DeterministicAutomaton &nonDeterministicAutomaton
, DeterministicAutomaton &result
, Vector<Set> &listOfCreatedStates
, const DeterministicAutomaton &automaton1)
{
	assert(listOfCreatedStates.getSize() == result.getNumberOfStates());

	const int indexOfCurrentState = listOfCreatedStates.getSize();

	//add the current states to the list of states
	listOfCreatedStates.push_back(elementsInCurrentState);

	//increase the size of the table of transitions by one row
	result.tableOfTransitions.resize(result.getNumberOfStates() + 1);

	//we'll use this iterator to traverse through all elements in the current set
	Set::Const_Iterator it = elementsInCurrentState.beginConst_Iterator();

	//if there is a final state in the list of states from which the current
	//state consists then the current state is also final
	for (it = elementsInCurrentState.beginConst_Iterator();
		it != elementsInCurrentState.endConst_Iterator();
		++it)
	{
		if (nonDeterministicAutomaton.isFinalState(*it))
		{
			//push the index of the current state to the list of final states
			result.orderedListOfFinalStates.push_back(indexOfCurrentState);
			break;
		}
	}

	Set elementsInTheNewState;

	//we want to find out the state that the automaton goes to from 
	//its current state, when it encounters a random symbol in it's alphabet
	for (int indexOfSymbol = 0;
		indexOfSymbol < numberOfElementsInTheTableOfTransitions;
		++indexOfSymbol)
	{
		for (it = elementsInCurrentState.beginConst_Iterator();
			it != elementsInCurrentState.endConst_Iterator();
			++it)
		{
			elementsInTheNewState.insert
				(nonDeterministicAutomaton.tableOfTransitions[*it][indexOfSymbol]);
		}

		//we still aren't ready with finding the states from which the new state consists
		//if some of this states is a final state in automaton1, then we must also add
		//the initial state of automaton2 to the set

		for (it = elementsInTheNewState.beginConst_Iterator();
			it != elementsInTheNewState.endConst_Iterator();
			++it)
		{
			if (automaton1.isFinalState(*it))
			{
				//we insert the index of the initial satate of automaton2
				//automaton1.getNumbarOfStates() is actually that index
				elementsInTheNewState.insert(automaton1.getNumberOfStates() );
				break;
			}
		}

		//now we know the indexes of the states which consist the new state

		int indexOfCreatedState;

		int indexOfNewState;

		//let's see if we have previously constructed a state with these elements;
		//we' ll scan through all created states to find out
		for (indexOfCreatedState = 0; indexOfCreatedState < listOfCreatedStates.getSize();
			++indexOfCreatedState)
		{
			if (elementsInTheNewState == listOfCreatedStates[indexOfCreatedState])
			{
				indexOfNewState = indexOfCreatedState;
				break;
			}
		}

		//if the state we have just constructed is a new state 
		//(isn't in the list of created states)
		if (indexOfCreatedState == listOfCreatedStates.getSize())
		{
			indexOfNewState = result.getNumberOfStates();

			constructConcatenationAutomaton
				(elementsInTheNewState
				, nonDeterministicAutomaton
				, result
				, listOfCreatedStates
				, automaton1);
		}
		elementsInTheNewState.clear();

		result.tableOfTransitions[indexOfCurrentState][indexOfSymbol] = indexOfNewState;
	}
}

bool DeterministicAutomaton::isInTheAlphabetOfTheAutomaton(unsigned char symbol)
{
	return (symbol >= firstValidSymbolInTheRegularExpression
		&&  symbol <= lastValidSymbolInTheRegularExpression)
		|| isspace(symbol);
}

int DeterministicAutomaton::getIndexOfTheSymbolInTheTableOfTransitions(unsigned char symbol)
{
	assert(isInTheAlphabetOfTheAutomaton(symbol));

	if (symbol >= firstValidSymbolInTheRegularExpression && symbol < 'a')
		return symbol - firstValidSymbolInTheRegularExpression;

	if (symbol >= 'a' && symbol <= 'z')
		return symbol - ('a' - 'A') - firstValidSymbolInTheRegularExpression;

	if (symbol > 'z' && symbol <= lastValidSymbolInTheRegularExpression)
		return symbol - ('z' + 1 - 'a') - firstValidSymbolInTheRegularExpression;

	//the last element in the table of transitions will be used for a random white character
	if (isspace(symbol))
		return indexOfRandomWhiteCharacter;

	assert(false);
}


//makes the elements of tableOfTransitions[indexOfStateInTheTableOfTransitions]
//in the interval [left; right]
//equal to indexOfStateThatTheTransitionIsGoingTo
void DeterministicAutomaton::
makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
(int indexOfStateInTheTableOfTransitions
, int left, int right, int indexOfStateThatTheTransitionIsGoingTo)
{
	for (int i = left; i <= right; ++i)
	{
		tableOfTransitions[indexOfStateInTheTableOfTransitions][i]
			= indexOfStateThatTheTransitionIsGoingTo;
	}
}

//checks if the state with index indexOfState is in the list of final states
//of the automaton
bool DeterministicAutomaton::isFinalState(int indexOfState)const
{
	//the elements of the vector, which stores the indexes of the final states
	//are ordered in ascending order
	//That's why we can perform a binary search

	int left = 0;

	int right = orderedListOfFinalStates.getSize() - 1;

	int middle;

	while (left <= right)
	{
		middle = (left + right) / 2;

		if ( indexOfState < orderedListOfFinalStates[middle])
		{
			right = middle - 1;
		}
		else
		{
			if (indexOfState > orderedListOfFinalStates[middle])
			{
				left = middle + 1;
			}
			else
			{
				assert(indexOfState == orderedListOfFinalStates[middle]);
				return true;
			}
		}
	}

	return false;
}
