// ChromosomePair.cpp: a pair of pointers to chromosomes

#include "ChromosomePair.h"


// ChromosomePair(): default constructor
ChromosomePair::ChromosomePair() : chrom1(NULL), chrom2(NULL)
{
}


// ChromosomePair(): constructor to create ChromosomePair from two Chromosome objects.
	// Precondition: None.
	// Postcondition: If the addresses of the chromosomes are not the same, then 
	//  chrom1 points to c1 and chrom2 points to c2; otherwise a warning has been printed
	//  and object becomes inactive.
ChromosomePair::ChromosomePair(Chromosome &c1, Chromosome &c2)
{
	activate(c1,c2);
}

// activate(): activates object
void ChromosomePair::activate(Chromosome &c1, Chromosome &c2)
{
	if (&c1 != &c2)
	{
		chrom1 = &c1<&c2?&c1:&c2;
		chrom2 = &c1<&c2?&c2:&c1;
	}
	else
	{
		cerr << "WARNING:ChromosomePair::ChromosomePair():chromosomes are the same" << endl;
	}
}

// end ChromosomePair.cpp
