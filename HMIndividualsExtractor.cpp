// HAPSIndividualsExtractor.cpp: Manages input from .haps files

#include "HMIndividualsExtractor.h"
#include <cctype>
#include <cmath>
#include <iostream>
using namespace std;


// HMIndividualsExtractor(): default constructor
HMIndividualsExtractor::HMIndividualsExtractor()
{}

void HMIndividualsExtractor::stripWhitespace()
{
	if (stream_phased.is_open())
	{
		char c;
		while((c=stream_phased.peek())!=EOF && isspace(c))
		stream_phased.get();
	}
	else
	{
		cerr << "WARNING:PolymorphicIndividualsExtractor::stripWhiteSpace():stream is not open" << endl;
		valid_flag = false;
	}
}

void HMIndividualsExtractor::loadInput()
{
	individualsP = &ALL_SAMPLES;

	ALL_SNPS.processLegendFile();
	ALL_SNPS.beginChromosome();
	numberOfMarkers = ALL_SNPS.size();

	while (stream_sample.good() && stream_phased.good()) getIndividuals();
	
	stream_sample.close();
	stream_phased.clear();
}


// getInput(): gets individuals from .haps file.
void HMIndividualsExtractor::getInput()
{

	cout << "Please enter the _legend file name" << endl;
	cin >> fileLegend;
	cout << "Please enter the _phased file name" << endl;
	cin >> filePhased;
	cout << "Please enter the _sample file name" << endl;
	cin >> fileSample;
	
	if ( !ALL_SNPS.setFile( fileLegend ) )
	{
		cerr << "WARNING:HMIndividualsExtractor::getInput():cannot open legend file" << endl;
		valid_flag = false;
		return;
	}

	stream_phased.open(filePhased.c_str());
	if (!stream_phased) 
	{
		valid_flag = false;
		cerr << "WARNING:HMIndividualsExtractor::getInput():cannot open phased file" << endl;
		return;
	}

	stream_sample.open(fileSample.c_str());
	if (!stream_sample) 
	{
		valid_flag = false;
		cerr << "WARNING: HMIndividualsExtractor::openFileStream(): sample stream could not be opened" << endl;
		return;
	}
}

// getIndividuals(): gets the next nuclear family from stream
void HMIndividualsExtractor::getIndividuals()
{
	string ID ,discard;
	
	streamoff offset = stream_phased.tellg(); if ( offset > 0 ) offset--;

	getline ( stream_phased , discard );
	if ( !stream_phased.good() ) return;
	offset_buffer = ( stream_phased.tellg() - offset);
	getline ( stream_phased , discard );
	stream_sample >> ID >> discard;
	if(ID == "") return;

	if ( HAPLOID )
	{
		Individual * new_ind[2];
		new_ind[0] = new Individual();
		new_ind[1] = new Individual();
		new_ind[0]->setOffset( offset );
		new_ind[1]->setOffset( offset );
		new_ind[0]->setID("0 " + ID + ".0" );
		new_ind[1]->setID("0 " + ID + ".1" );
		
		individualsP->addIndividual( new_ind[0] );
		individualsP->addIndividual( new_ind[1] );
	} else
	{
		Individual * new_ind = new Individual;
		new_ind->setID(ID);
		new_ind->setOffset( offset );
		individualsP->addIndividual(new_ind);
	}
}

void HMIndividualsExtractor::getCompleteMarkerSet(Individual * p0 , Individual * p1 )
{
	MarkerSet * ms[2];
	ms[0] = new MarkerSet();
	ms[1] = new MarkerSet();

	loadMarkerSet( p0->getOffset() , ms );

	p0->addMarkerSet(TRANS,ms[0]);
	p1->addMarkerSet(TRANS,ms[1]);

	stream_phased.clear();
}

void HMIndividualsExtractor::loadMarkerSet( streamoff offset , MarkerSet ** ms )
{
	unsigned int maxsize = ALL_SNPS.currentSize();
	for(int al=0;al<2;al++)
	{
			stream_phased.seekg(
				offset
				+ 2 * ALL_SNPS.getROIStart().getMarkerNumber()
				+ 2 * position_ms * MARKER_SET_SIZE 
				+ al * ( offset_buffer - 1 )
				);

		for (int position = 0; position < MARKER_SET_SIZE; position++)
		{
			if(position_ms*MARKER_SET_SIZE+position >= maxsize) break;
			
			stripWhitespace();
			char marker = stream_phased.peek();
			if ( marker == '1' ) ms[al]->set(position , true );

			stream_phased.get();
		}
	}
}

void HMIndividualsExtractor::getCompleteMarkerSet(Individual * p)
{
	MarkerSet * ms[2];
	ms[0] = new MarkerSet();
	ms[1] = new MarkerSet();
	loadMarkerSet( p->getOffset() , ms );

	p->addMarkerSet(UNTRANS,ms[0]);
	p->addMarkerSet(TRANS,ms[1]);

	stream_phased.clear();
}

// end HMIndividualsExtractor.cpp
