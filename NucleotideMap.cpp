// NucleotideMap.cpp: maps characters to nucleotides

#include "NucleotideMap.h"
#include <iostream>
using namespace std;


// NucleotideMap(): default constructor
NucleotideMap::NucleotideMap()
{
}


// map(): maps characters to nucleotides
Nucleotide NucleotideMap::map(char Char) const
{
	if (Char == 'A' || Char == 'a')
		return A;
	else if (Char == 'C' || Char == 'c')
		return C;
	else if (Char == 'G' || Char == 'g')
		return G;
	else if (Char == 'T' || Char == 't')
		return T;
	else
	{
		cerr << "WARNING:NucleotideMap::map():character not a nucleotide character" << endl;
		return A;
	}
}


// map(): maps integers to nucleotides
Nucleotide NucleotideMap::map(int Int) const
{
	if (Int == 1)
		return A;
	else if (Int == 2)
		return C;
	else if (Int == 3)
		return G;
	else if (Int == 4)
		return T;
	else
	{
		cerr << "WARNING:NucleotideMap::map():integer not a nucleotide integer" << endl;
		return A;
	}
}


// mapC(): maps integers represented as characters to nucleotides
Nucleotide NucleotideMap::mapC(char IntC) const
{
	if (IntC == '1')
		return A;
	else if (IntC == '2')
		return C;
	else if (IntC == '3')
		return G;
	else if (IntC == '4')
		return T;
	else
	{
		cerr << "WARNING:NucleotideMap::mapC(): character not a nucleotide integer" << endl;
		return A;
	}
}


// mapNC(): maps Nucleotide objects into characters
char NucleotideMap::mapNC(Nucleotide nt) const
{
	if (nt == A)
		return 'A';
	else if (nt == C)
		return 'C';
	else if (nt == G)
		return 'G';
	else // (nt == T)
		return 'T';
}

// end NucleotideMap.cpp
