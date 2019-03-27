// PolymorphicIndividualsExtractor.cpp: Abstract base class to extract individuals 
//   from various file formats

#include "PolymorphicIndividualsExtractor.h"
#include <cctype>
#include <fstream>
#include <iostream>
using namespace std;


// PolymorphicIndividualsExtractor(): default constructor
PolymorphicIndividualsExtractor::PolymorphicIndividualsExtractor()
: individualsP(NULL), valid_flag(true)
{}

void PolymorphicIndividualsExtractor::setPhased(bool p)
{
	phased = p;
}

bool PolymorphicIndividualsExtractor::valid()
{
	return valid_flag;
}

// end PolymorphicIndividualsExtractor.cpp
