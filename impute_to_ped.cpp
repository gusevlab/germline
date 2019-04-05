#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <list>
#include <string.h>
#include <stdlib.h>

using namespace std;

int main (int argc, char* argv[])
{
	string line, discard;
	if(argc < 3){
		cerr << "Usage: " << argv[0] << " <haps file> <sample file> <output>" << endl;
		return 1;
	}
	ifstream file_haps(argv[1]);
	ifstream file_samp(argv[2]);
	if(!file_haps || !file_samp) { cerr << "file could not be opened" << endl; return 1; }

	string pre = argv[3];
	ofstream file_ped( (pre + ".ped").c_str() );
	ofstream file_map( (pre + ".map").c_str() );

	// get individuals
	string map_field[3];
	vector< string > fam;
	stringstream ss;
	// skip first two lines
	getline(file_samp,line);
	getline(file_samp,line);
	while(getline(file_samp,line)) {
		ss.clear(); ss.str( line );
		ss >> map_field[0] >> map_field[1];
		fam.push_back( map_field[0] + " " + map_field[1] + " 0 0 0 0" );
	}
	file_samp.close();

	string * seq = new string[ fam.size() ];
	cout << fam.size() << " samples" << endl;

	// read all data
	int snp_ctr = 0;
	char al[2] , inp;
	string cur_al;
	while(getline(file_haps,line))
	{
		ss.clear(); ss.str( line );
		ss >> map_field[0] >> map_field[1] >> map_field[2] >> al[0] >> al[1];
		// cout << al[0] << '\t' << al[1] << endl;
		if(map_field[0] == "") continue;

		file_map << map_field[0] << " " << map_field[1] << " 0 " << map_field[2] << endl;

		// read haplotype
		for(int i=0;i< fam.size() ;i++)
		{
			ss >> inp;
			cur_al = string( 1 , al[ inp - '0' ] );
			if(snp_ctr == 0) seq[i] = cur_al;
			else seq[i] += " " + cur_al;

			ss >> inp;
			cur_al = string( 1 , al[ inp - '0' ] );
			seq[i] += " " + cur_al;
		}
		snp_ctr++;
	}
	file_haps.close();
	file_map.close();

	// print all markers
	for (int i = 0; i < fam.size(); i++) file_ped << fam[i] << " " << seq[i] << endl;
	file_ped.close();
	return 0;
}
