// MatchFactory.cpp: Generates matches from individuals

#include "MatchFactory.h"


// MatchFactory(): default constructor
MatchFactory::MatchFactory()
{}

void MatchFactory::assertShares()
{
	for ( iter = segments.begin() ; iter != segments.end() ; iter++ )
	{
		iter->second.assertMatches();
	}
}

int MatchFactory::size()
{
	return (int)segments.size();
}

// initialize(): initializes object
void MatchFactory::initialize()
{
	segments.clear();
}	
void MatchFactory::hash( Individual * i )
{
	int haps , het = i->numHet();
	
	if ( het == 0 || HAPLOID ) haps = 1;
	else haps = 2;

	if ( ALLOW_HOM && het <= MAX_ERR_HOM + MAX_ERR_HET ) i->assertHomozygous();
	if ( HOM_ONLY ) return;
	
	for ( int c = 0 ; c < haps ; c++ )
	{
		boost::dynamic_bitset<>& ms = i->getChromosome(c)->getMarkerSet()->getMarkerBits();
		if ( (iter = segments.find( ms )) == segments.end() )
			segments.insert( make_pair ( ms , Share( i ) ) );
		else
			iter->second.add( i );
	}
}

// end MatchFactory.cpp
