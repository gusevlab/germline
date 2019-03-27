// MatchesBuilder.h: builds matches from individuals

#ifndef MATCHESBUILDER_H
#define MATCHESBUILDERs_H

#include "BasicDefinitions.h"
#include "Individuals.h"
#include "MatchFactory.h"
#include "PolymorphicIndividualsExtractor.h"
#include <sstream>
#include <iostream>

class MatchesBuilder
{

public:

	// MatchesBuilder(): default constructor
	// Precondition: None.
	// Postcondition: individualsP and matchesP are
	//  set to NULL.
	MatchesBuilder( PolymorphicIndividualsExtractor* );

	// buildMatches(): builds matches from individuals
	// Precondition: None.
	// Postcondition: mats contains all matches from inds;
	//  individualsP points to inds; matchesP points to mats.
	void buildMatches();

	void printAllMatches();
	void printHaplotypes(string);

private:

	// matchAllMarkers(): builds matches for individuals considering all markers.
	// Precondition: individualsP points to a valid Individuals object and matchesP
	//  points to a valid Matches object.
	// Postcondition: matchesP points to a valid Matches object containing
	//   all matches for individuals considering all markers
	void matchAllMarkers();
	void readAllMarkers();


	// matchMarkerSet(): builds matches for individuals considering markers in marker set.
	// Precondition: individualsP points to a valid Individuals object and matchesP
	//  points to a valid Matches object.
	// Postcondition: matchesP points to a valid Matches object containing all 
	//   matches for individuals considering markers in marker set markerSetPosition, 
	//   extending existing matches whenever possible.
	void matchMarkerSet();
	void readMarkerSet();
	void readHaploidMarkerSet();

	// pointer to individuals
	Individuals * individualsP;
	// generates matches
	MatchFactory matchFactory;
	// pie to extract each word independantly
	PolymorphicIndividualsExtractor* pieP;

	unsigned int ms_start, ms_end;
}; 

#endif 

// end MatchesBuilder.h
