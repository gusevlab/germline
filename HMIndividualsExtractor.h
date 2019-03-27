#ifndef HMINDIVIDUALSEXTRACTOR_H
#define HMINDIVIDUALSEXTRACTOR_H

#include "BasicDefinitions.h"
#include "NucleotideMap.h"
#include "PolymorphicIndividualsExtractor.h"
#include <string>
using namespace std;

class HMIndividualsExtractor : public PolymorphicIndividualsExtractor
{
public:

	// HAPSIndividualsExtractor(): default constructor
	// Precondition: None.
	// Postcondition: inputFile has been obtained from user
	//  and snps has been populated.
	HMIndividualsExtractor();

	// getInput(): gets input from .haps file
	// Precondition: Input is a .haps file in a valid format
	// Postcondition: inds points to individuals from
	//   .haps file
    void getInput();
	void loadInput();
	void getCompleteMarkerSet(Individual * p);
	void getCompleteMarkerSet(Individual * p0 , Individual * p1 );

private:

    void getIndividuals();
	void loadMarkerSet( streamoff offset , MarkerSet ** ms );
	void stripWhitespace();

	NucleotideMap inp;
	string fileLegend, filePhased, fileSample;
	ifstream stream_phased , stream_sample;
	int offset_buffer;
};

#endif

// end HAPSIndividualsExtractor.h
