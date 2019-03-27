
#include "Individual.h"

Share::Share( Individual * cip )
{
	add( cip );
}

void Share::assertMatches()
{
	list<Individual*>::iterator i , ii;
	Match * m;

	for ( i = matches.begin() ; i != matches.end() ; i++ )
	{
		ii = i;
		for ( ++ii ; ii != matches.end() ; ii++ )
		{
			// Check if this pair matched in previous word (symmetrically)
			m = (*i)->getMatch( (*ii)->getNumericID() );
			if ( m == NULL ) m = (*ii)->getMatch( (*i)->getNumericID() );

			if ( m != NULL )
			{
				// This match can be incremented
				m->end_ms = position_ms;
			}
			else
			{
				// This match must be created
				m = createMatch( *i , *ii );
				// Extend the match backwards
				m->extendBack();
				// Mark asserted
				(*i)->addMatch( (*ii)->getNumericID() , m );
			}
		}
	}
}

Match * Share::createMatch(Individual * c1 , Individual * c2)
{
	Match * new_match = new Match();
	new_match->end_ms = new_match->start_ms = position_ms;

	new_match->node[0] = c1;
	new_match->node[1] = c2;

	return new_match;
}

void Share::add(Individual * cip)
{
	matches.push_back( cip );
}
