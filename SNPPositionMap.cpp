// SNPPositionMap.cpp: Map from SNP IDs to positions in Info file

#include "SNPPositionMap.h"
#include <iostream>
using namespace std;


// SNPPositionMap(): default constructor
SNPPositionMap::SNPPositionMap()
{
}


// retrievePosition(): retrieves position for a SNP ID
int SNPPositionMap::retrievePosition(string SNPID)
{
	if (snpPosMap.find(SNPID)!=snpPosMap.end())
		return snpPosMap[SNPID];
	else
		return -1;
}


// sizeOfMap(): returns size of map
int SNPPositionMap::sizeOfMap()
{
	return (int)snpPosMap.size();
}


// storeMapping(): stores mapping from SNP ID to position
void SNPPositionMap::storeMapping(string SNPID, int position)
{
	if (position >= 0)
		snpPosMap[SNPID] = position;
	else
	{
		cerr << "WARNING:SNPPositionMap::storeMapping():position is not positive"
			<< endl;
	}
}


// end SNPPositionMap.cpp
