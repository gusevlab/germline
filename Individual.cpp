// Individual.cpp: An individual with genetic data

#include "Individual.h"
using namespace std;

// Individual(): default constructor
Individual::Individual()
{
	if ( HAPLOID ) h = new Chromosome[1]; else h = new Chromosome[2];
	numeric_id = 0;
}

Individual::~Individual()
{
	delete[] h;
	delete[] all_matches;
}

void Individual::freeMatches()
{
	for ( size_t iter = 0 ; iter < num_samples ; iter++ )
		if ( all_matches[ iter ] != NULL ) deleteMatch( iter );
}

Match * Individual::getMatch( size_t id )
{
	return all_matches[ id ];
}

void Individual::assertHomozygous()
{
	size_t iter = this->getNumericID();
	Match * m;
	if ( all_matches[ iter ] != NULL )
	{
		// increment this match
		all_matches[ iter ]->end_ms = position_ms;

	} else
	{	
		// this is a new match
		m = new Match();
		m->end_ms = m->start_ms = position_ms;
		m->node[0] = m->node[1] = this;
		m->extendBack();
		all_matches[ iter ] = m;
	}
}

void Individual::assertShares()
{
	Match * m;
	set<Individual*>::iterator cip;

	// try to extend previous matches that did not match currently
	for( size_t iter = 0 ; iter < num_samples ; iter++ )
	{
		if ( all_matches[ iter ] == NULL ) continue;

		m = all_matches[ iter ];
		// Can we increment?
		if ( m->approxEqual() ) m->end_ms = position_ms;
		else deleteMatch( iter );
	}
}

void Individual::clearMatch( size_t id )
{
	all_matches[ id ] = NULL;
}
void Individual::deleteMatch( size_t id )
{
	// try to print it
	all_matches[ id ]->print( MATCH_FILE );
	delete all_matches[ id ];

	// erase from the list
	clearMatch( id );
}

void Individual::addMatch( size_t id , Match * m)
{
	all_matches[ id ] = m;
}

void Individual::reserveMemory()
{
	all_matches = new Match * [ num_samples ];
	for ( size_t i = 0 ; i < num_samples ; i++ ) all_matches[ i ] = NULL;
}

void Individual::print(ostream& out,long start,long end)
{
	short tot;
	if ( HAPLOID ) tot=1; else tot=2;
	for(int i=0;i<tot;i++)
	{
		out << getID() << '\t';
		h[i].print(out,start,end);
		out << endl;
	}
}

int Individual::numHet()
{
	if ( HAPLOID ) return 0;
	else return int(( h[0].getMarkerSet()->getMarkerBits() ^ h[1].getMarkerSet()->getMarkerBits() ).count());
}

bool Individual::isHeterozygous()
{
	if ( HAPLOID ) return false;
	else return !( h[0].getMarkerSet()->equal( h[1].getMarkerSet() ) );
}

bool Individual::isHeterozygous(int i)
{
	if ( HAPLOID ) return false;
	else return h[0].getMarkerSet()->getMarker(i) != h[1].getMarkerSet()->getMarker(i);
}

void Individual::setOffset(streamoff o)
{
	offset = o;
}

streamoff Individual::getOffset()
{
	return offset;
}

// getID(): accessor for ID
string Individual::getID() const
{
	return ID;
}

Chromosome * Individual::getAlternateChromosome( Chromosome * c)
{
	if ( HAPLOID ) return &(h[0]);
	else
	{
		if( &(h[0]) == c ) return &(h[1]); else return &(h[0]);
	}
}

Chromosome * Individual::getChromosome(int ct)
{
	if ( HAPLOID ) ct = 0;

	return &(h[ct]);
}

unsigned int Individual::getNumericID()
{
	return numeric_id;
}

void Individual::setNumericID( unsigned int id )
{
	numeric_id = id;
}

// setID(): mutator for ID.
void Individual::setID(string id)
{
	ID = id;
}

void Individual::clearMarkers()
{
	h[0].clear();
	if ( !HAPLOID ) h[1].clear();
}

// addMarkerSet(): adds MarkerSet to a chromosome
void Individual::addMarkerSet(int ct, MarkerSet * ms)
{
	if ( HAPLOID ) ct = 0;
	h[ct].addMarkerSet(ms);
}

// operator<<(): overloaded stream insertion operator
ostream& operator<<(ostream &fout, Individual& ind)
{
	fout << ind.getID() << endl;
	fout << ind.getChromosome(0) << endl;
	fout << ind.getChromosome(1) << endl;
	return fout;
}


// end Individual.cpp
