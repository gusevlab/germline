// Individuals.h: A collection of individuals

#ifndef INDIVIDUALS_H
#define INDIVIDUALS_H

#include "BasicDefinitions.h"
#include "Chromosome.h"
#include "Individual.h"
#include <map>
#include <ostream>
using namespace std;

class Individual;
class Individuals
{
public:

	// Individuals(): default constructor
	// Precondition: None.
	// Postcondition: individuals is empty.
	Individuals();
	~Individuals();

	// addIndividual(): adds an Individual object
	// Precondition: None.
    // Postcondition: ind has been added to individuals
	void addIndividual( Individual * ind );
	Individual * getIndividual ( size_t id ) { return pedigree[ id ]; }

	bool more();
	Individual* next();
	void begin();
	size_t size() { return pedigree.size(); }
	void initialize();
	void print( ostream& );
	
	void freeMatches();
	void freeMarkers();

private:

	void permuteMarkerSet(Chromosome *, int, MarkerSet);
	// stores the individuals
	vector< Individual * > pedigree;
	size_t iter;

	long sets;
};

#endif

// end Individuals.h
