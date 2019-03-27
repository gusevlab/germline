// SNPs.cpp: SNPs in order of marker position along the chromosome

#include "SNPs.h"
#include <iostream>
using namespace std;


// SNPs(): default constructor
SNPs::SNPs()
{}

unsigned int SNPs::currentSize()
{
	if ( ROI && chromosome == ROI_chromosome )
		return ( ROI_snp[1] - ROI_snp[0] ) + 1;
	else
		return int(chromosome->second.size() );
}

unsigned int SNPs::size()
{
	return full_size;
}

string SNPs::getChromosome()
{
	return chromosome->first;
}

void SNPs::beginChromosome()
{
	if ( ROI ) chromosome = ROI_chromosome;
	else chromosome = genome.begin();
}
bool SNPs::moreChromosome()
{
	return chromosome != genome.end();
}
void SNPs::nextChromosome()
{
	chromosome++;
}

bool SNPs::setFile( string f )
{
	s.open( f.c_str() );
	if( !s ) return false;
	else return true;
}

float SNPs::getDistance(unsigned int start_marker, unsigned int end_marker)
{
	bool genetic;
	return getDistance( start_marker, end_marker, genetic);
}

float SNPs::getDistance(unsigned int start_marker, unsigned int end_marker , bool& genetic)
{
	if ( end_marker >= chromosome->second.size() ) end_marker = (unsigned int) chromosome->second.size() - 1;
	if ( start_marker < 0 ) start_marker = 0;
	
	if ( chromosome->second[start_marker].getCentimorgan() == -1 || chromosome->second[end_marker].getCentimorgan() == -1 )
	{
		genetic = false;
		return ( chromosome->second[end_marker].getPhysPos() - chromosome->second[start_marker].getPhysPos() ) / 1e6f;
	}
	else
	{
		genetic = true;
		return chromosome->second[end_marker].getCentimorgan() - chromosome->second[start_marker].getCentimorgan();
	}
}

void SNPs::setGeneticDistances()
{
	unsigned int scan , left , right , ctr;
	float cur_genet;
	vector< float > genet;

	for ( map< string , vector<SNP> >::iterator chr = genome.begin() ; chr != genome.end() ; chr++ )
	{
		genet.clear();
		for ( unsigned int i = 0 ; i < chr->second.size(); i++ )
		{
			if ( chr->second[ i ].getCentimorgan() == -1 )
			{
				scan = left = right = i;
				while ( scan > 0 && chr->second[ i ].getPhysPos() - chr->second[ --scan ].getPhysPos() < 100e3 )
					if ( chr->second[ scan ].getCentimorgan() != -1 ) { left = scan; break; }
				scan = i;
				while ( ++scan < chr->second.size() && chr->second[ scan ].getPhysPos() - chr->second[ i ].getPhysPos() < 100e3 )
					if ( chr->second[ scan ].getCentimorgan() != -1 ) { right = scan; break; }
				
				if ( chr->second[ left ].getCentimorgan() != -1 && chr->second[ right ].getCentimorgan() != -1 )
				{
					if ( (chr->second[ i ].getPhysPos() - chr->second[ left ].getPhysPos()) < (chr->second[ right ].getPhysPos() - chr->second[ i ].getPhysPos()) )
						cur_genet = chr->second[ left ].getCentimorgan();
					else
						cur_genet = chr->second[ right ].getCentimorgan();
				} else if ( chr->second[ left ].getCentimorgan() != -1 ) { cur_genet = chr->second[ left ].getCentimorgan();
				} else if ( chr->second[ right ].getCentimorgan() != -1 ) { cur_genet = chr->second[ right ].getCentimorgan();
				} else cur_genet = -1;
				genet.push_back( cur_genet );
			}
		}

		ctr = 0;
		for ( unsigned int i = 0 ; i < chr->second.size(); i++ )
		{
			if ( chr->second[ i ].getCentimorgan() == -1 ) chr->second[i].setCentimorgan( genet[ctr++] );
		}
	}
}

void SNPs::loadGeneticDistanceMap(string f)
{
	ifstream s_map( f.c_str() );
	if(!s_map) { cerr << "WARNING: Genetic map \"" << f << "\" could not be loaded" << endl; return; }

	string in , rs , chr;
	map< string , map< string , float > >::iterator chr_query;
	float d;

	while(s_map.good())
	{
		s_map >> chr >> rs >> d >> in;
		if ( ( chr_query = cm_map.find( chr ) ) == cm_map.end() )
			chr_query = cm_map.insert( make_pair( chr , map< string , float >() ) ).first;
		chr_query->second.insert(make_pair(rs,d));
	}
}

// getSNP(): accessor for SNPS.
SNP SNPs::getSNP(unsigned int markerPosition) const
{
	if (!chromosome->second.empty() && markerPosition >= 0 && markerPosition < chromosome->second.size())
		return chromosome->second[markerPosition];
	else
	{
		return chromosome->second.back();
	}
}


// getVariant(): accessor for variant alleles
char SNPs::getVariant(unsigned int index, int variant) const
{
	if (index >= 0 && index < chromosome->second.size())
	{
		if (variant == 0 || variant == 1)
			return chromosome->second[index].getVariant(variant);
		else
		{
			cerr << "WARNING:SNPs::getVariant():variant is not 0 or 1"
				<< endl;
			return A;
		}
	}
	else
	{
		cerr << "WARNING:SNPs::getVariant():index is out of bounds for snps"
			<< endl;
		return A;
	}
}

void SNPs::print( ostream& out )
{
	for ( list< map< string , vector<SNP> >::iterator >::iterator chr = chr_list.begin() ; chr != chr_list.end() ; chr++ )
	{
		for ( vector<SNP>::iterator i = (*chr)->second.begin() ; i != (*chr)->second.end() ; i++ )
		{
			out << i->getChr() << '\t' << i->getSNPID() << '\t' << i->getCentimorgan() << '\t' << i->getPhysPos() << endl;
		}
	}
}

// setmapNucleotideToBinary: If both alleles have been set, return the mapping
// otherwise, set & save the allele (1st allele = major/1, 2nd allele = minor/0)
int SNPs::mapNucleotideToBinary(char nt, unsigned int index)
{
	return chromosome->second[index].mapNucleotide(nt);
}

void SNPs::setROI( string rsid[2] )
{
	ROI_id[0] = rsid[0];
	ROI_id[1] = rsid[1];
}

void SNPs::processMAPFile(){

	string chr , rsid, discard;
	long bppos;
	bool in_region = false;
	int gen_ctr = 0;
	float gen_dist;
	SNP cur;
	for ( full_size = 0 ; s.good() ; full_size++ )
	{	
		rsid = "";
		s >> chr >> rsid >> gen_dist >> bppos;
		if( rsid == "" ) break;
		
		cur.setChr(chr);
		cur.setSNPID(rsid);
		cur.setPhysPos( bppos );
		cur.setMarkerNumber( full_size );

		if ( getGeneticDistance( cur ) != -1 ) { cur.setCentimorgan( getGeneticDistance( cur ) ); gen_ctr++; }
		else if ( gen_dist > 0 ) { cur.setCentimorgan( gen_dist ); gen_ctr++; }
		else cur.setCentimorgan(-1);

		addSNP( cur );

		if( ROI && !in_region)
		{
			if( rsid == ROI_id[0] ) { in_region = true; ROI_snp[0] = full_size; ROI_chromosome = chromosome; }
			else continue;
		}
		if( ROI && in_region )
		{
			if( rsid == ROI_id[1] )
			{
				in_region = false;
				ROI_snp[1] = full_size;
				if ( chromosome != ROI_chromosome )
				{
					cerr << "WARNING: Region of interest spans multiple chromosomes - " 
						 << ROI_chromosome->first 
						 << " and " << chromosome->first << endl;
					ROI = false;
				}
			}
		}

	}
	setGeneticDistances();
	s.close();
}

void SNPs::addSNP( SNP& new_snp )
{
	if( (chromosome = genome.find( new_snp.getChr() )) == genome.end() )
	{
		vector<SNP> v; v.push_back( new_snp );
		chr_list.push_back( genome.insert( make_pair( new_snp.getChr() , v ) ).first );
		chromosome = genome.begin();

	}
	else
	{
		chromosome->second.push_back( new_snp );
	}
}

// processLegendFile(): processes HapMap legend file
void SNPs::processLegendFile()
{
	string rsid, discard;
	char al[2];
	long bppos;
	int gen_ctr = 0;
	SNP cur;
	bool in_region = false;
	// skip the first line
	getline(s,discard);
	for ( full_size = 0 ; s.good() ; full_size++ )
	{
		// track progress
		rsid = "";
		s >> rsid >> bppos >> al[0] >> al[1];
		if ( rsid == "" ) continue;

		cur.setSNPID(rsid);
		cur.setPhysPos( bppos );
		cur.setVariant(0,al[0]);
		cur.setVariant(1,al[1]);
		cur.setMarkerNumber ( full_size );
		cur.setCentimorgan( getGeneticDistance( cur ) );
		if ( cur.getCentimorgan() != -1 ) gen_ctr++;
		cur.setChr( "0" );
		addSNP( cur );

		if( ROI && !in_region)
		{
			if( rsid == ROI_id[0] ) { in_region = true; ROI_snp[0] = full_size; ROI_chromosome = chromosome; }
			else continue;
		}
		if( ROI && in_region )
		{
			if( rsid == ROI_id[1] ) { in_region = false; ROI_snp[1] = full_size; }
		}
	}
	if ( !SILENT ) cout << gen_ctr << " SNPs have genetic distance" << endl;
	s.close();

	setGeneticDistances();
}

float SNPs::getGeneticDistance( SNP cur )
{
	map< string , map< string , float > >::iterator c = cm_map.find( cur.getChr() );
	if ( c != cm_map.end() )
	{
		map< string , float >::iterator i = c->second.find( cur.getSNPID() );
		if ( i != c->second.end() )
			return i->second;
	}
	return -1;
}

SNP SNPs::getROIStart()
{
	if( ROI && ROI_chromosome == chromosome ) return chromosome->second[ROI_snp[0]];
	else return chromosome->second.front();
}

SNP SNPs::getROIEnd()
{
	if( ROI && ROI_chromosome == chromosome ) return chromosome->second[ROI_snp[1]];
	else return chromosome->second.back();
}

// stripWhiteSpace(): strips whitespace from stream
void SNPs::stripWhiteSpace(ifstream& stream)
{
	if (stream.is_open())
	{
		char c;
		while((c=stream.peek())!=EOF && isspace(c))
			stream.get();
	}
	else
	{
		cerr << "WARNING:SNPs::stripWhiteSpace():stream is not open" << endl;
	}
}


// end SNPs.cpp
