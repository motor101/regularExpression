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

#ifndef DETERMINISTIC_AUTOMATON_H
#define DETERMINISTIC_AUTOMATON_H

#include <fstream>
#include "vectorSpecification.h"
#include "specialConstantsDeclarations.h"
#include "arraySpecification.h"
#include "setSpecification.h"

namespace fmi
{
namespace sdp
{
	class DeterministicAutomaton
	{
	public:
		//constructs a deterministic automaton, which can recognize simpleRegularExpression;
		//simpleRegularExpression must be "", or a string with one letter or a special string
		//special strings start with initialSymbolForSpecialStrings and are elements of
		//the list of special strings
		DeterministicAutomaton(const char *simpleRegularExpression = "");

	public:
		//scans the input file line by line and prints out the lines that bring it to a final state
		void scanTextFile(std::ifstream &inputFile, const char *nameOfFile) const;

		//returns the number of states of the automaton
		int getNumberOfStates() const;

		//returns the number of final states of the automaton
		int getNumberOfFinalStates() const;
	public:
		static DeterministicAutomaton makeConcatenation
			(const DeterministicAutomaton &automaton1, const DeterministicAutomaton &automaton2);

		static DeterministicAutomaton makeUnion
			(const DeterministicAutomaton &automaton1, const DeterministicAutomaton &automaton2);

		static DeterministicAutomaton makeClosure(const DeterministicAutomaton &automatonThatWeWantoToClose);

	private:
		//represents the transforming of a non-deterministic automaton,
		//which is a union of two deterministic automatons, into a 
		//deterministic automaton - result;
		//listOfCreated represents the set of states which comprise
		//the already created states
		static void constructUnionAutomaton
			( const Set &elementsInCurrentState
			, const DeterministicAutomaton &nonDeterministicAutomaton
			, DeterministicAutomaton &result
			, Vector<Set> &listOfCreatedStates);


		//represents the transforming of a non-deterministic automaton,
		//which is a concatenation of two deterministic automatons: automaton1
		//and automaton2, into a 
		//deterministic automaton - result;
		//listOfCreated represents the set of states which comprise
		//the already created states
		static void constructConcatenationAutomaton
			( const Set &elementsInCurrentState
			, const DeterministicAutomaton &nonDeterministicAutomaton
			, DeterministicAutomaton &result
			, Vector<Set> &listOfCreatedStates
			, const DeterministicAutomaton &automaton1);

		//represents the transforming of a non-deterministic automaton,
		//which is a closure of a deterministic automaton - 
		//automatonThatWeWantToClose, into a deterministic automaton - 
		//result;
		//listOfCreated represents the set of states which comprise
		//the already created states
		static void constructClosureAutomaton
			( const Set &elementsInCurrentState
			, const DeterministicAutomaton &automatonThatWeWantoToClose
			, DeterministicAutomaton &result
			, Vector<Set> &listOfCreatedStates);

	private:

		//the number of all valid symbols for a regular expression
		//minus the number of lowercase letters
		//plus a special element representing a random white character
		//
		//The automaton doesn't differentiate between lowercase and uppercase letters
		//That's why we'll memorize them in one place
		static const int numberOfElementsInTheTableOfTransitions =
			(specialConstants::lastValidSymbolInTheRegularExpression + 1
			- specialConstants::firstValidSymbolInTheRegularExpression)
			- ('z' + 1 - 'a')
			+ 1;

		static const int indexOfInitialState = 0;

		//we'll use the last column in the table of transitions to store the information
		//about white characters
		static const int indexOfRandomWhiteCharacter = numberOfElementsInTheTableOfTransitions - 1;
		
	private:

		static bool isInTheAlphabetOfTheAutomaton(unsigned char symbol);

		static int getIndexOfTheSymbolInTheTableOfTransitions(unsigned char symbol);

		//makes the elements of tableOfTransitions[indexOfStateInTheTableOfTransitions]
		//in the interval [left; right]
		//equal to indexOfStateThatTheTransitionIsGoingTo
		void makeTheElementsOfTheArrayOfTransitionInTheIntervalLeftRightEqualToIndexOfState
			(int indexOfStateInTheTableOfTransitions
			, int left, int right, int indexOfStateThatTheTransitionIsGoingTo);

		//checks if the state with index indexOfState is in the list of final states
		//of the automaton
		bool isFinalState(int indexOfState)const;

	private:
		Vector<int> orderedListOfFinalStates;

		Vector <Array <numberOfElementsInTheTableOfTransitions> > tableOfTransitions;
		
	};

}	//sdp
}	//fmi

#endif //DETERMINISTIC_AUTOMATON_H