// MatchFactory.h: Generates matches from individuals

#ifndef MATCHFACTORY_H
#define MATCHFACTORY_H

#include "MarkerSet.h"
#include "Individual.h"
#include <map>
#include <vector>

using namespace std;

class MatchFactory
{
	
public:

	// MatchFactory(): default constructor
	// Precondition: None.
	// Postcondition: segments and matches are empty and position is -1.
	MatchFactory();

	int size();

    // initialize(): initializes object
	// Precondition:  None.
	// Postcondition: If 0=<pos, then position is set to pos and map is empty;
	//  otherwise an error message is printed.
	void initialize();

	void hash(Individual *);
	void assertShares();

private:

	// stores data to check for matches
	map < boost::dynamic_bitset<> , Share > segments;
	map < boost::dynamic_bitset<> , Share >::iterator iter;
};

#endif

// end MatchFactory.h
