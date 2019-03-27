// GERMLINE.h: GEnetic Relationship Miner by LINear Extension

#ifndef GERMLINE_H
#define GERMLINE_H

#include "InputManager.h"
#include "Individuals.h"
#include "MatchesBuilder.h"
#include "BasicDefinitions.h"
#include <iostream>
#include <ctime>

class GERMLINE
{
	
public:

	// GERMLINE(): default constructor
	// Precondition: None.
	// Postcondition: None
	GERMLINE();

	// mine(): main function for GERMLINE
	// Precondition: Input files are in standard formats.
	// Postcondition: Matching chromosome segments have been
	//  printed to matches.dat in a readable format.
	void mine( string params );

private:

	// Manages input to individuals
	InputManager inputManager;
};

#endif

// end GERMLINE.h
