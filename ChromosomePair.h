// ChromosomePair.h: a pair of pointers to chromosomes

#ifndef CHROMOSOMEPAIR_H
#define CHROMOSOMEPAIR_H

#include "BasicDefinitions.h"
#include "Chromosome.h"
#include <iostream>
using namespace std;

class ChromosomePair
{
public:

	// ChromosomePair(): default constructor
	// Precondition: None.
	// Postcondition: Pointers to chromosomes are NULL.
	ChromosomePair();

    // ChromosomePair(): constructor to create ChromosomePair from two Chromosome objects.
	// Precondition: None.
	// Postcondition: If the addresses of the chromosomes are not the same, then 
	//  chrom1 points to c1 or c2 with smaller reference and chrom2 points to 
	//  c1 or c2 with larger reference; otherwise a warning has been printed
	//  and object becomes inactive.
	ChromosomePair(Chromosome &c1, Chromosome &c2);

	// activate(): activates object
	// Precondition: None.
	// Postcondition: If the addresses of c1 and c2 are not the same, then chrom1 points 
	//  to c1 or c2 with smaller reference and chrom2 points to c1 or c2 with larger 
	//  reference; otherwise a warning has been printed. 
	void activate(Chromosome &c1, Chromosome &c2);

private:

	// pointer to first chromosome in pair
	Chromosome* chrom1;
	// pointer to second chromosome in pair
	Chromosome* chrom2;

};


// operator<(): overloaded less than operator
// Precondition: None.
// Postcondition: If the reference of cp1.chrom1 is less than the
//  reference of cp2.chrom1, and, in the case of a tie, if the reference
//  of cp1.chrom2 is less than the reference of cp2.chrom2, then returns true; 
//  otherwise returns false. 
bool operator<(const ChromosomePair &cp1, const ChromosomePair &cp2);


#endif

// end ChromosomePair.h
