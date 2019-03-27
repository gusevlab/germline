// InputManager.h: Manages input 

#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "BasicDefinitions.h"
#include "PolymorphicIndividualsExtractor.h"
#include "Individuals.h"
#include <string>
using namespace std;

class InputManager
{
public:

	// InputManager(): default constructor
	// Precondition: None.
	// Postcondition: User has been queried and memory for
	//  the appropriate PolymorphicIndividualsExtractor has
	//  been allocated..
	InputManager();
	~InputManager();

	// getIndividuals(): extracts individuals using pie
	// Precondition: None.
	// Postcondition: inds contains the individuals from the
	//  input files that user supplies in the format 
	//  corresponding to pie. .
	void getIndividuals();
	string getOutput();
	PolymorphicIndividualsExtractor* getPie();

	bool getPhased();

private:

	// normalPrompt(): issues prompt asking user which file format 
	//  will be used for individuals
	// Precondition: None.
	// Postcondition: An appropriate prompt has been issued to stdout.
	void normalPrompt();

	// validChoice(): determines if a string is valid input for file format
	// Precondition: None.
	// Postcondition:If string is a valid entry for file format according
	//  to information from normalPrompt(), then returns true; 
	//  otherwise returns false
	bool validChoice(string choice);

	// invalidChoiceMessage(): gives message saying choice is not valid
	// Precondtion: None.
	// Postcondition: Message saying choice is not valid has been printed to stdout
	void invalidChoiceMessage();

	// setFileFormat(): sets file format using information from normalPrompt()
	// Precondition: None.
	// Postcondition: If choice is a valid choice, then FileFormat has been set 
	//  according to information from normalPrompt(); otherwise a warning message
	//  has been printed.
	void setFileFormat(string choice);

	// instantiatePie(): instantiates appropriate pie
	// Precondition: format contains the correct file format.
	// Postcondition: pie has been instantiated with the correct extractor.
	void instantiatePie();

	// type of file format
	FileFormat format;

	// extracts individuals from various file formats
	PolymorphicIndividualsExtractor * pie;

};

#endif

// end InputManager.h
