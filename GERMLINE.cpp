// GERMLINE.cpp: GEnetic Relationship Miner for LINear Extension

#include "GERMLINE.h"
#include "math.h"
#include <iostream>

using namespace std;

ofstream MATCH_FILE;
size_t num_samples;
unsigned long num_matches;
SNPs ALL_SNPS;
Individuals ALL_SAMPLES;

// GERMLINE(): default constructor
GERMLINE::GERMLINE()
{}

// mine(): main function for GERMLINE
void GERMLINE::mine( string params )
{
	PolymorphicIndividualsExtractor * pie = inputManager.getPie();
	inputManager.getIndividuals();
	if ( ! pie->valid() ) return;
	string out;
	if ( out_file == "" ) out = inputManager.getOutput();
	else out = out_file;
	
	num_samples = 0;
	num_matches = 0;

	pie->loadInput();
	MatchesBuilder mb( pie );

	ofstream fout( ( out + ".log" ).c_str() );

	fout << setw(65) << setfill('-') << ' ' << endl << setfill(' ');
	fout << " Welcome to GERMLINE, a tool for detecting long segments shared" << endl;
	fout << " by descent between pairs of individuals in near-linear time." << endl;
	fout << endl;
	fout << " For more details, please see the paper [ PMID: 18971310 ]" << endl;
	fout << " or the web-site [ http://gusevlab.org/software/ ]" << endl;
	fout << endl;
	fout << " GERMLINE was coded by Alexander Gusev and collaborators in " << endl;
	fout << " Itsik Pe'er's Computational Biology Lab at Columbia University" << endl;
	fout << setw(65) << setfill('-') << ' ' << endl << setfill(' ');
	
	if ( BINARY_OUT ) MATCH_FILE.open( ( out + ".bmatch" ).c_str() , ios::binary );
	else MATCH_FILE.open( ( out + ".match" ).c_str() );
	
	fout << params << endl;
	fout << setw(65) << setfill('-') << ' ' << endl << setfill(' ');
	fout << setw(50) << left << "Minimum match length: " << MIN_MATCH_LEN << " cM" << endl;
	fout << setw(50) << "Allowed mismatching bits: " << MAX_ERR_HOM << " " << MAX_ERR_HET << endl;
	fout << setw(50) << "Word size: " << MARKER_SET_SIZE << endl;
	if ( ROI )
		fout << setw(50) << "Target region: " << ALL_SNPS.getROIStart().getSNPID() << " - " << ALL_SNPS.getROIEnd().getSNPID() << endl;
	else
		fout << setw(50) << "Target region: " << "all" << endl;
	
	time_t timer[2]; time( &timer[0] );
	
	if ( DEBUG ) cout << "DEBUG MODE ON" << endl;

	if ( ROI )
	{
		ALL_SNPS.beginChromosome();
		num_sets = (long)ceil((double)ALL_SNPS.currentSize()/(double)MARKER_SET_SIZE);
		mb.buildMatches();
		ALL_SAMPLES.freeMatches();
		ALL_SAMPLES.freeMarkers();
	}
	else
	{
		for ( ALL_SNPS.beginChromosome() ; ALL_SNPS.moreChromosome() ; ALL_SNPS.nextChromosome() )
		{
			num_sets = (long)ceil((double)ALL_SNPS.currentSize()/(double)MARKER_SET_SIZE);
			mb.buildMatches();
			if ( !SILENT ) cout << "Matches completed ... freeing memory" << endl;
			ALL_SAMPLES.freeMatches();
			ALL_SAMPLES.freeMarkers();
		}
	}

	time( &timer[1] );

	fout << setw(50) << "Total IBD segments: " << num_matches << endl;
	fout << setw(50) << "Total runtime (sec): " << difftime( timer[1] , timer[0] ) << endl;
	fout.close();

	if ( DISTRIB_OUT ) {
		for ( int i = 0 ; i < hist_ctr.size() - 1 ; i++ ) MATCH_FILE << hist_ctr[i] << endl;
	}

	MATCH_FILE.close();

	if ( BINARY_OUT )
	{
		ofstream bmid_out( ( out + ".bmid" ).c_str() );
		ALL_SNPS.print( bmid_out );
		bmid_out.close();

		ofstream bsid_out( ( out + ".bsid" ).c_str() );
		ALL_SAMPLES.print( bsid_out );
		bsid_out.close();
	}
}


// end GERMLINE.cpp
