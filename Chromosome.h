// Chromosome.h.haplotyped markers for a chromosome

#ifndef CHROMOSOME_H
#define CHROMOSOME_H

#include "BasicDefinitions.h"
#include "MarkerSet.h"
#include <vector>
using namespace std;

class Chromosome
{
public:

	// Chromosome(): default constructor
	// Precondition: None.
	// Postcondition: chromosome is empty. maxSets is 0.
	Chromosome();
	
	// getMarkerSet(): accessor for MarkerSet objects.
	// Precondition: None.
	// Postcondition: If index refers to an index for which memory has been
	//   allocated, then the MarkerSet at position index has been returned;
	//   otherwise a warning is printed and the default MarkerSet is returned.
	MarkerSet* getMarkerSet();
	MarkerSet* getMarkerSet(unsigned int);

	// addMarkerSet(): adds a MarkerSet
	// Precondition: None.
	// Postcondition: If chromosome does not yet have maxSets MarkerSet objects, 
	//  then ms is added to the end of chromosome; otherwise a warning is printed.
	void addMarkerSet(MarkerSet * ms);
	void clear();

	void print(ostream& out,unsigned int,unsigned int);
	void print_snps(ostream& out, unsigned int, unsigned int);

private:

	// Storage for chromosome MarkerSet objects
	vector<MarkerSet * > chromosome;
};

ostream &operator<<(ostream &fout, Chromosome&);

#endif

// end Chromosome.h
