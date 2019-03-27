// Individuals.cpp: A collection of individuals

#include "Individuals.h"
#include <iostream>
using namespace std;


// Individuals(): default constructor
Individuals::Individuals()
{}

Individuals::~Individuals()
{
	for(begin();more();next())
		delete pedigree[ iter ];
}

void Individuals::initialize()
{
	for ( iter = 0 ; iter < pedigree.size() ; iter++ ) pedigree[ iter ]->reserveMemory();
}

void Individuals::freeMatches()
{
	for(begin();more();next()) pedigree[ iter ]->freeMatches();
}

void Individuals::freeMarkers()
{
	for(begin();more();next()) { pedigree[ iter ]->clearMarkers(); }
}

void Individuals::print( ostream& out )
{
	for(begin();more();next())
		out << pedigree[ iter ]->getID() << endl;
}

void Individuals::begin()
{
	iter = 0;
}

bool Individuals::more()
{
	return iter < pedigree.size();
}

Individual * Individuals::next()
{
	return pedigree[ iter++ ];
}

// addIndividual(): adds an Individual object
void Individuals::addIndividual(Individual * ind)
{
	pedigree.push_back(ind);
	ind->setNumericID( (unsigned int) num_samples++ );
}

// end Individuals.cpp
