// NucleotideMap.h: maps objects to nucleotides

#ifndef NUCLEOTIDEMAP_H
#define NUCLEOTIDEMAP_H

#include "BasicDefinitions.h"

class NucleotideMap
{
public:

	// NucleotideMap(): default constructor
	// Precondition: None.
	// Postcondition: None.
	NucleotideMap();

	// map(): maps characters to nucleotides
	// Precondition: None.
	// Postcondition: If character is A, C, G, or T, case-insensitive,
	//   then corresponding Nucleotide has been returned; otherwise
	//   a warning has been printed and A has been returned.
	Nucleotide map(char Char) const;

	// map(): maps integers to nucleotides
	// Precondition: None.
	// Postcondition: If Int is 1-4, then corresponding Nucleotide 
	//   according to map, 1->A, 2->C, 3->G, 4->T, has been returned; otherwise
	//   a warning has been printed and A has been returned.
	Nucleotide map(int Int) const;

	// mapC(): maps integers represented as characters to nucleotides
	// Precondition: None.
	// Postcondition: If character is 1-4, then corresponding Nucleotide 
	//   according to map, 1->A, 2->C, 3->G, 4->T, has been returned; otherwise
	//   a warning has been printed and A has been returned.
	Nucleotide mapC(char IntC) const;

	// mapNC(): maps Nucleotide objects into characters
	// Precondition: None.
	// Postcondition: Character A, C, G, or T, corresponding to nt has been returned.
	char mapNC(Nucleotide nt) const;
};

#endif

// end NucleotideMap.h
