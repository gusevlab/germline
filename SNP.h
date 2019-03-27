// SNP.h: Stores a SNP's information

#ifndef SNP_H
#define SNP_H

#include "BasicDefinitions.h"
#include <string>
#include <vector>
using namespace std;

class SNP
{
public:

	// SNP(): default constructor
	// Precondition: None.
	// Postcondition: strings have been initialized to empty.
	//  variants has two members with 0 mapped to A and 1 mapped to C. 
	SNP();

	int mapNucleotide(char);

	// getSNPID(): accessor for SNPID
	// Precondition: None.
	// Postcondition: Returns SNPID.
	string getSNPID() const;

	// getPhysPos(): accessor for physPos
	// Precondition: None.
	// Postcondition: Returns physPos.
	long getPhysPos() const;

	string getChr() const;

	// getVariant(): accessor for variants
	// Precondition: None.
	// Postcondition: If i is 0 or 1, return the
	//  variant nucleotide that is mapped to i; otherwise
	//  issue a warning message and returns A.
	char getVariant(int i) const;

	// setSNPID(): mutator for SNPID
	// Precondition: None.
	// Postcondition: SNPID is set to sid.
	void setSNPID(const string& sid);

	// setPhysPos(): mutator for physPos
	// Precondition: None.
	// Postcondition: physPos is set to pp.
	void setPhysPos(long pp);

	// setVariant(): mutator for variants
	// Precondition: None.
	// Postcondition: If i is 0 then variant0 is set to nt;
	//  else if i is 1 then variant1 is set to nt; otherwise
	//  a warning is issued.
	void setVariant(int i, char nt);
	void setChr(const string& c);
	
	void setCentimorgan( float cm );
	float getCentimorgan();

	void setMarkerNumber( unsigned int );
	unsigned int getMarkerNumber();

private:

	// SNP ID 
	string SNPID;
	// physical position of SNP
	long physPos;
	// genetic distance position of SNP
	float centimorgan;
	// allele variant mapped to 0
	char variant[2];
	// chromosome number
	string chr;
	// have variants been set 1 == major, 2 == both
	short varSet;
	// frequency 
	unsigned int count[2];
	// marker number
	unsigned int num;
};

#endif

// end SNP.h
