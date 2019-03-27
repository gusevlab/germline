// SNPs.h: SNPs in order of marker position along the chromosome

#ifndef SNPS_H
#define SNPS_H

#include "BasicDefinitions.h"
#include "NucleotideMap.h"
#include "SNP.h"
#include "SNPPositionMap.h"
#include "math.h"
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <list>
using namespace std;

class SNPs
{
public:

	// SNPs(): default constructor
	// Precondition: None.
	// Postcondition: None.
	SNPs();

	unsigned int size();
	unsigned int currentSize();

	void setROI(string rsid[2]);
	SNP getROIStart();
	SNP getROIEnd();
	string getChromosome();

	void loadGeneticDistanceMap(string);
	void setGeneticDistances();

	// getSNP(): accessor for SNPS.
	// Precondition: None.
	// Postcondition: If snps has been populated and if markerPosition
	//  is within bounds of snps, then returns the SNP in markerPosition
	//  position of snps; otherwise issues a warning and returns an inactive SNP.
	SNP getSNP(unsigned int markerPosition) const;
	
	// Returns genetic distance if possible, otherwise returns physical distance (in MB)
	float getDistance(unsigned int , unsigned int);
	float getDistance(unsigned int , unsigned int , bool& genetic);

    // getVariant(): accessor for variant alleles
	// Precondition: None.
	// Postcondition: If index is within bounds of snps and variant is 0 or 1,
	//  then returns the variant nucleotide that is mapped to variant in snp
	//  corresponding to index; otherwise issue a warning message and returns A.
	char getVariant(unsigned int index, int variant) const;

	int mapNucleotideToBinary(char nt, unsigned int index);

	// processLegendFile(): parses HapMap legend file for markers
	// Precondition: "info" contains valid .legend file name
	// Postcondition: "snps" contains all SNP ids and positions, with counting starting at 0
	void processLegendFile();

	// processMAPFile(): parse PLINK .map file for markers
	// Precondition: "info" contains valid .map file name
	// Postcondition: "snps" contains all SNP ids and positions, with counting starting at 0
	void processMAPFile();

	bool setFile( string );
	void print( ostream& );

	void beginChromosome();
	bool moreChromosome();
	void nextChromosome();

private:

	// stripWhiteSpace(): strips whitespace from stream
	// Precondition: stream is a valid istream
	// Postcondition: Leading whitespace has been stripped.
	void stripWhiteSpace(ifstream& stream);

	float getGeneticDistance( SNP );

	void addSNP(SNP&);

	// info file
	string info;
	ifstream s;
	unsigned int full_size;
	
	// genetic map
	map< string , map< string , float > > cm_map;

	// snps
	map< string , vector<SNP> > genome;
	map< string , vector<SNP> >::iterator chromosome;
	map< string , vector<SNP> >::iterator ROI_chromosome;
	// keep a list of the chromosomes in input order
	list< map< string , vector<SNP> >::iterator > chr_list;

	NucleotideMap cnm;

	string ROI_id[2];
	int ROI_snp[2];
};

#endif

// end SNPs.h
