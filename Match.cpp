#include "Match.h"

void Match::extendBack()
{
	// save old position values
	unsigned int SAVE_pms = position_ms;
	
	// iterate backwards through genome
	while(position_ms > 0)
	{
		position_ms--;
		if( !approxEqual() )
		{
			position_ms++;
			break;
		}
	}
	start_ms = position_ms;
	// restore saved values
	position_ms = SAVE_pms;
}

bool Match::approxEqual()
{
	// homozygosity check
	if ( node[0] == node[1] )
	{
		if ( ALLOW_HOM )
		{
			if ( (int) ( node[0]->getChromosome( 0 )->getMarkerSet()->getMarkerBits() ^ node[1]->getChromosome( 1 )->getMarkerSet()->getMarkerBits() ).count() 
				 <= ( MAX_ERR_HOM + MAX_ERR_HET ) ) return true; else return false;
		}
		else
		{
			return false;
		}
	}
	else
	{
		// 1. Haplotype extension
		if ( HAPLOID )
		{
				if ( (int)(node[0]->getChromosome( 0 )->getMarkerSet()->getMarkerBits() ^ node[1]->getChromosome( 0 )->getMarkerSet()->getMarkerBits()).count() <= MAX_ERR_HOM ) return true;
		} else
		{
			for ( int a = 0 ; a < 2 ; a++ ) {
				for ( int b = 0 ; b < 2 ; b++ ) { 
					if ( (int)(node[0]->getChromosome( a )->getMarkerSet()->getMarkerBits() ^ node[1]->getChromosome( b )->getMarkerSet()->getMarkerBits()).count() <= MAX_ERR_HOM )
					{
						return true;
					}
				}
			}
		}

		if ( HAPLOID || HAP_EXT ) return false;

		// 2. Genotype extension
		// identify common homozygous SNPs
		boost::dynamic_bitset<> mask
			= ( node[0]->getChromosome( 0 )->getMarkerSet()->getMarkerBits() ^ node[0]->getChromosome( 1 )->getMarkerSet()->getMarkerBits() ).flip()
			& ( node[1]->getChromosome( 0 )->getMarkerSet()->getMarkerBits() ^ node[1]->getChromosome( 1 )->getMarkerSet()->getMarkerBits() ).flip();

		// assert that homozygous SNPs are identical
		if ( (int) ((node[0]->getChromosome( 0 )->getMarkerSet()->getMarkerBits() ^ node[1]->getChromosome( 0 )->getMarkerSet()->getMarkerBits()) & mask).count() <= MAX_ERR_HET )
		{
			return true;
		}
		else return false;
	}
}

int Match::scanLeft( unsigned int ms )
{
	bool err = false;
	int marker = MARKER_SET_SIZE - 1;

	if ( HAPLOID ) {
		for ( marker = MARKER_SET_SIZE - 1 ; marker >= 0 && ! err; marker-- )
			if ( node[0]->getChromosome( 0 )->getMarkerSet()->getMarkerBits()[marker] != node[1]->getChromosome( 0 )->getMarkerSet()->getMarkerBits()[marker] )
				err = true;
	} else if ( HAP_EXT )
	{
		int cur_marker;
		marker = 0;
		for ( int a = 0 ; a < 2 ; a++ ) {
			for ( int b = 0 ; b < 2 ; b++ ) { 
				if ( node[0] == node[1] && b <= a ) continue;
				err = false;
				for ( cur_marker = MARKER_SET_SIZE - 1 ; cur_marker >= 0 && ! err; cur_marker-- )
				{
					if ( node[0]->getChromosome( a )->getMarkerSet()->getMarkerBits()[cur_marker] != node[1]->getChromosome( b )->getMarkerSet()->getMarkerBits()[cur_marker] )
						err = true;
				}
				if ( cur_marker > marker ) marker = cur_marker;
			}
		}
	} else
	{
	boost::dynamic_bitset<> mask
		= ( node[0]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[0]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).flip()
		& ( node[1]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[1]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).flip();
	mask = ( node[0]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[1]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits()) & mask;

	for( marker = MARKER_SET_SIZE - 1 ; marker >= 0 && !err ; marker-- )
		if ( mask[marker] ) err = true;
	}
	
	return marker;
}

int Match::scanRight( unsigned int ms )
{
	bool err = false;
	int marker = 0;

	if ( HAPLOID ) {
		for ( marker = 0 ; marker < MARKER_SET_SIZE && ! err; marker++ )
			if ( node[0]->getChromosome( 0 )->getMarkerSet()->getMarkerBits()[marker] != node[1]->getChromosome( 0 )->getMarkerSet()->getMarkerBits()[marker] )
				err = true;
	} else if ( HAP_EXT )
	{
		int cur_marker;
		marker = MARKER_SET_SIZE;

		for ( int a = 0 ; a < 2 ; a++ ) {
			for ( int b = 0 ; b < 2 ; b++ ) { 
				if ( node[0] == node[1] && b <= a ) continue;
				err = false;
				for ( cur_marker = 0 ; cur_marker < MARKER_SET_SIZE && ! err; cur_marker++ )
				{
					if ( node[0]->getChromosome( a )->getMarkerSet()->getMarkerBits()[cur_marker] != node[1]->getChromosome( b )->getMarkerSet()->getMarkerBits()[cur_marker] )
						err = true;
				}
				if ( cur_marker < marker ) marker = cur_marker;
			}
		}
	} else
	{
	boost::dynamic_bitset<> mask
		= ( node[0]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[0]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).flip()
		& ( node[1]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[1]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).flip();
	mask = ( node[0]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[1]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits()) & mask;

	for( marker = 0 ; marker < MARKER_SET_SIZE && !err ; marker++ )
		if ( mask[marker] ) err = true;
	}	
	return marker;
}

int Match::diff( unsigned int ms )
{
	boost::dynamic_bitset<> mask
		= ( node[0]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[0]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).flip()
		& ( node[1]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[1]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).flip();
	mask = ( node[0]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[1]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits()) & mask;

	return int(mask.count());
}

bool Match::isHom( int n , unsigned int ms )
{
	return (int) ( node[n]->getChromosome( 0 )->getMarkerSet(ms)->getMarkerBits() ^ node[n]->getChromosome( 1 )->getMarkerSet(ms)->getMarkerBits() ).count() <= ( MAX_ERR_HOM + MAX_ERR_HET );
}

void Match::print( ostream& fout )
{
	// extend this match from both ends
	unsigned int snp_start = ALL_SNPS.getROIStart().getMarkerNumber() + start_ms * MARKER_SET_SIZE;
	unsigned int snp_end = ALL_SNPS.getROIStart().getMarkerNumber() + ( end_ms + 1 ) * MARKER_SET_SIZE - 1;
	int marker;

	
	if ( WIN_EXT )
	{
		// backwards
		if( start_ms > 0 )
		{
			marker = scanLeft( start_ms - 1 );
			snp_start -= (MARKER_SET_SIZE - marker - 2);
		}
	}
	if ( WIN_EXT || end_ms == num_sets - 2 )
	{
		// forwards
		if( end_ms < num_sets - 1 )
		{
			marker = scanRight( end_ms + 1 );
			snp_end += marker - 1;
		}
	}
	

	bool genetic;
	float distance;
	if ( ( distance = ALL_SNPS.getDistance(snp_start,snp_end,genetic)) < MIN_MATCH_LEN ) return;
	// print

	// get hamming distance & ignored bit count
	int dif = 0;
	for( unsigned int i = start_ms; i <= end_ms ; i++) { dif += diff( i ); }
	
	// calculate if homozygous
	bool hom[2];
	if ( node[0] == node[1] ) { hom[0] = hom[1] = 1; }
	else
	{
		for ( int n = 0 ; n < 2 ; n++ )
		{
			hom[n] = true;
			for ( unsigned int i = start_ms ; i<= end_ms && hom ; i++ )
			{
				hom[n] = isHom( n , i );
			}
		}
	}

	if ( DISTRIB_OUT ) {
		// Just add it to the histogram
		for ( int i = 0 ; i < hist_win.size()-1 ; i++ ){
			if ( distance >= hist_win[i] && distance < hist_win[i+1] ) {
				hist_ctr[i]++;
				break;
			}
		}
	} else if ( MINIMAL_OUT ) {
		fout << node[0]->getID() << '\t';
		fout << node[1]->getID() << '\t';
		fout << setiosflags(ios::fixed) << setprecision(3) << distance << endl;
	} else if ( BINARY_OUT )
	{
		unsigned int pid[2];
		pid[0] = node[0]->getNumericID();
		pid[1] = node[1]->getNumericID();
		unsigned int sid[2];
		sid[0] = ALL_SNPS.getSNP(snp_start).getMarkerNumber();
		sid[1] = ALL_SNPS.getSNP(snp_end).getMarkerNumber();
		fout.write( (char*) &pid[0] , sizeof( unsigned int ) );
		fout.write( (char*) &pid[1] , sizeof( unsigned int ) );
		fout.write( (char*) &sid[0] , sizeof( unsigned int ) );
		fout.write( (char*) &sid[1] , sizeof( unsigned int ) );
		fout.write( (char*) &dif , sizeof( int ) );
		fout.write( (char*) &hom[0] , sizeof( bool ) );
		fout.write( (char*) &hom[1] , sizeof( bool ) );
	} else
	{
		fout << node[0]->getID() << '\t';
		fout << node[1]->getID() << '\t';
		fout << ALL_SNPS.getSNP(snp_start).getChr() << '\t';
		fout << ALL_SNPS.getSNP(snp_start).getPhysPos() << ' ';
		fout << ALL_SNPS.getSNP(snp_end).getPhysPos() << '\t';
		fout << ALL_SNPS.getSNP(snp_start).getSNPID() << ' ';
		fout << ALL_SNPS.getSNP(snp_end).getSNPID() << '\t';
		fout << ( snp_end - snp_start + 1) << '\t';
		fout << setiosflags(ios::fixed) << setprecision(3) << distance << '\t';
		if ( genetic ) fout << "cM" << '\t'; else fout << "MB" << '\t';
		fout << dif;
		for ( int n = 0 ; n < 2 ; n++ )
			if ( hom[n] ) fout << '\t' << 1; else fout << '\t' << 0;
		fout << endl;
	}
	num_matches++;
}

