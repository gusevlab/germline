// PolymorphicIndividualsExtractor.h: Abstract base class to extract individuals 
//   from various file formats

#ifndef POLYMORPHICINDIVIDUALSEXTRACTOR_H
#define POLYMORPHICINDIVIDUALSEXTRACTOR_H

#include "Individuals.h"
#include "SNPs.h"
#include <fstream>
#include <string>
#include <vector>
using namespace std;

class PolymorphicIndividualsExtractor
{
public:

	// PolymorphicIndividualsExtractor(): default constructor
	// Precondition: None.
	// Postcondition: individualsP has been set to NULL, 
	//  numberOfMarkers has been set to 0, and names for
	//  CSV files and INFO file have been been obtained from
	//  user.
	// Note: snps is not yet populated because then there
	//  would be a delay before prompting for the input file
	//  which depends on the derived class for validation.
	PolymorphicIndividualsExtractor();

	// getInput(): virtual function to extract input
	// Precondition: None.
	// Postcondition: Input has been stored in the
	//  memory pointed to by inds
    virtual void getInput() = 0;
	virtual void loadInput() = 0;
	virtual void getCompleteMarkerSet(Individual *) = 0;
	virtual void getCompleteMarkerSet(Individual * , Individual *) = 0;

	void setPhased(bool);
	bool valid();

protected:

	// pointer to individuals
	Individuals* individualsP;
	// number of markers per individual
	int numberOfMarkers;
	// stores weather or not the data is phased
	bool phased;
	// stores flag for valid input
	bool valid_flag;

};

#endif

// end PolymorphicIndividualsExtractor.h
