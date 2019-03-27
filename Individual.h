// Individual.h: An individual with genetic data

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "BasicDefinitions.h"
#include "Chromosome.h"
#include "Match.h"
#include "Individuals.h"
#include <string>
#include <list>
#include <map>
#include <set>
#include <iostream>

using namespace std;

class Individual;
class Match;
class Share
{
public:
	Share( Individual * );
	void add(Individual * );
	void assertMatches();

private:
	Match * createMatch(Individual * c1 , Individual * c2);
	list< Individual * > matches;
};


class Individual
{
public:

	/** Match Tracking **/
	void reserveMemory();

	void addShare(Share*);
	void assertShares();
	void assertHomozygous();

	list<Share*>& getShareList();

	void freeMatches();
	Match * getMatch( size_t );

	void deleteMatch( size_t );
	void clearMatch( size_t );
	void addMatch( size_t , Match* );

	/** Match Tracking **/
	void print(ostream&,long,long);
	bool isHeterozygous();
	bool isHeterozygous(int i);
	int numHet();
	
	// Individual(): default constructor
	// Precondition: None.
	// Postcondition: All strings and vectors are initialized
	//  to empty. sex is initialized to MALE.
	//  affected is initialized to false.
	Individual();
	~Individual();

	// getID(): accessor for ID
	// Precondition: None.
	// Postcondition: Returns value for ID
	string getID() const;

	void setOffset(streamoff);
	streamoff getOffset();

	// getChromosome(): accessor for Chromosome references
	// Precondition: None.
	// Postcondition: returns reference to Chromosome chrom.
	Chromosome* getChromosome(int);
	Chromosome* getAlternateChromosome(Chromosome * );

	// setID(): mutator for ID.
	// Precondition: None.
	// Postcondition: ID has been set to id.
	void setID(string id);
	void setNumericID( unsigned int id );
	unsigned int getNumericID();

	// addMarkerSet(): adds MarkerSet to a chromosome
	// Precondition: None.
	// Postcondition: If chromosome identified by ct has room, then ms has been
	//  added to the end of the chromosome; otherwise a warning message is printed..
	void addMarkerSet(int, MarkerSet * ms);

	// clearMarkers(): clears all MarkerSets from this individual
	void clearMarkers();

private:

	// ID of the individual
	string ID;
	unsigned int numeric_id;

	Chromosome * h;
	// sequence start in file
	streamoff offset;
	
	Match ** all_matches;
};


// operator<<(): overloaded stream insertion operator
// Precondition: fout is a value ostream.
// Postcondition: ind has been sent to fout.
ostream &operator<<(ostream &fout, Individual& ind);

#endif

// end Individual.h
