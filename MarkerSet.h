// MarkerSet.h: a marker set of the size to be used for hashing

#ifndef MARKERSET_H
#define MARKERSET_H

#include "BasicDefinitions.h"
#include "SNPs.h"
#include <boost/dynamic_bitset.hpp>
#include <list>
using namespace std;

class MarkerSet
{
public:

	// MarkerSet(): default constructor
	// Precondition: None.
	// Postcondition: all markers have been initialized to 0.
	MarkerSet();
	MarkerSet(const MarkerSet&);

	void clear();
	void set( int , bool );

	void print(ostream&);
	void print(ostream&, unsigned int, unsigned int);

	boost::dynamic_bitset<>& getMarkerBits();

    // getMarker(): gets marker
	// Precondition: None.
	// Postcondition: If 0<=index<MARKER_SET_SIZE, then ith marker
	//  has been returned; otherwise a warning has been printed and
	//  0 has been returned.
	bool getMarker(int index) const;

	// equal(): compares another MarkerSet to see if it has the 
	//  same markers as this object.
	// Precondition: None.
	// Postcondition: If m2 has the same markers as this object,
	//  then returns true; otherwise returns false.
	bool equal(MarkerSet * ms);

	int diff(MarkerSet * ) const;

private:
	// markers stored as a bitset to allow for fast comparisons
	boost::dynamic_bitset<> markers;
};

// operator<<:overloaded insertion operator
// Precondition: fout is a valid stream.
// Postcondition: ms has been sent to fout.
ostream& operator<<(ostream& fout, const MarkerSet& m1);


#endif

// end MarkerSet.h
