// MatchesBuilder.cpp: builds matches from individuals

#include "MatchesBuilder.h"

unsigned int position_ms;
unsigned int num_sets;

int ALLOWED_MASKED;

// MatchesBuilder(): default constructor
MatchesBuilder::MatchesBuilder( PolymorphicIndividualsExtractor * pie )
{
	individualsP = & ALL_SAMPLES;
	pieP = pie;
}

// buildMatches(): builds matches from individuals
void MatchesBuilder::buildMatches()
{
	if ( !SILENT ) cout << "Read Markers" << endl;
	ms_start = 0; ms_end = num_sets;
	readAllMarkers();

	if ( !SILENT ) cout << "Match Markers" << endl;
	matchAllMarkers();
}

void MatchesBuilder::printHaplotypes(string fout_name)
{
	ofstream fout( fout_name.c_str() );

	for(individualsP->begin();individualsP->more();)
	{
		individualsP->next()->print(fout,0,num_sets);
	}
	fout.close();
}

// matchAllMarkers(): builds matches for individuals considering all markers
void MatchesBuilder::matchAllMarkers()
{
	for (position_ms = ms_start; position_ms < ms_end - 1; position_ms++)
	{
		if ( !SILENT ) cerr << "\rMatching Markers - " << (position_ms*100) / (ms_end - 1) << "%" << flush;
		matchMarkerSet();
	}
	if ( !SILENT ) cerr << '\r' << "Matching Markers Complete" << endl;
}

void MatchesBuilder::readAllMarkers()
{
	for (position_ms = ms_start; position_ms < ms_end; position_ms++)
	{
		if ( !SILENT ) cerr << "\rReading Markers - " << position_ms*100/ms_end << "%" << flush;
		if ( HAPLOID ) readHaploidMarkerSet(); else readMarkerSet();
	}
	if ( !SILENT ) cerr << '\r' << "Reading Markers Complete" << endl;
}

void MatchesBuilder::readHaploidMarkerSet()
{
	// Read the individuals two at a time

	Individual * i[2];
	for(individualsP->begin();individualsP->more();)
	{
		i[0] = individualsP->next();
		i[1] = individualsP->next();
		pieP->getCompleteMarkerSet( i[0] , i[1] );
	}
}

void MatchesBuilder::readMarkerSet()
{
	Individual * i;
	for(individualsP->begin();individualsP->more();)
	{
		i = individualsP->next();
		pieP->getCompleteMarkerSet(i);
	}
}

// matchMarkerSet(): builds matches for individuals considering markers in marker set.
void MatchesBuilder::matchMarkerSet()
{
	// Match:
	for(individualsP->begin();individualsP->more();)
		matchFactory.hash( individualsP->next() );

	// Verify:
	matchFactory.assertShares();

	// Extend:
	for(individualsP->begin();individualsP->more();)
		individualsP->next()->assertShares();
	
	matchFactory.initialize();
}

// end MatchesBuilder.cpp
