// SNPPositionMap.h: Map from SNP IDs to positions in Info file

#ifndef SNPPOSITIONMAP_H
#define SNPPOSITIONMAP_H

#include <map>
#include <string>
using namespace std;

class SNPPositionMap
{
public:

	// SNPPositionMap(): default constructor
	// Precondition: None.
	// Postcondition: None.
	SNPPositionMap();

	// retrievePosition(): retrieves position for a SNP ID
	// Precondition: None.
	// Postcondition: If SNPID is in snpPosMap, then the corresponding
	//  position from the infoFile has been returned; otherwise -1 has
	//  been returned.
	int retrievePosition(string SNPID);

	// storeMapping(): stores mapping from SNP ID to position
	// Precondition: None.
	// Postcondition: If position is positive, then SNPID has been associated
	//  with position; otherwise a warning has been printed. 
	void storeMapping(string SNPID, int position);

	// sizeOfMap(): returns size of map
	// Precondition: None.
	// Postcondition: size of map is returned
	int sizeOfMap();

private:

	// actual map
	map<string,int> snpPosMap;
};

#endif

// end SNPPositionMap.h
