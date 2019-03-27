#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <iomanip>

using namespace std;

struct Marker
{
	short	chr;
	string	rsid;
	float	cm_distance;
	long	bp_distance;
};

float get_distance( Marker& m_left , Marker& m_right , bool& genetic )
{
	if ( m_left.cm_distance == -1 || m_right.cm_distance == -1 )
	{
		genetic = false;
		return m_right.bp_distance - m_left.bp_distance;
	} else
	{
		genetic = true;
		return m_right.cm_distance - m_left.cm_distance;
	}
}

int main (int argc, char* argv[])
{
	if(argc != 4){
			cerr << "Usage: " << argv[0] << " [BMATCH FILE] [BSID FILE] [BMID FILE]" << endl;
			return 0;
	}
	
	string line, discard;
	ifstream file_bmatch( argv[1] , ios::binary );
	ifstream file_bsid( argv[2] );
	ifstream file_bmid( argv[3] );
	if(!file_bmatch || !file_bsid || !file_bmid ) { cerr << "file could not be opened" << endl; return 0; }

	stringstream ss;
	
	// load samples
	vector< string > sample_id;
	while( getline(file_bsid , line) )
	{
		sample_id.push_back( line );
	}
	file_bsid.close();
	
	// load markers
	vector< Marker > marker_id;
	Marker cur_marker;
	while ( getline(file_bmid , line) )
	{
		ss.clear(); ss.str( line );
		ss >> cur_marker.chr >> cur_marker.rsid >> cur_marker.cm_distance >> cur_marker.bp_distance;
		marker_id.push_back( cur_marker );
	}
	file_bmid.close();
	
	// load matches
	unsigned int pid[2];
	unsigned int sid[2];
	int dif;
	bool hom[2] , genetic;
	while ( file_bmatch.good() )
	{
		pid[0] = -1;
		file_bmatch.read( (char*) &pid[0] , sizeof( unsigned int ) );
		if ( pid[0] == -1 ) continue;
		file_bmatch.read( (char*) &pid[1] , sizeof( unsigned int ) );
		file_bmatch.read( (char*) &sid[0] , sizeof( unsigned int ) );
		file_bmatch.read( (char*) &sid[1] , sizeof( unsigned int ) );
		file_bmatch.read( (char*) &dif , sizeof( int ) );
		file_bmatch.read( (char*) &hom[0] , sizeof( bool ) );
		file_bmatch.read( (char*) &hom[1] , sizeof( bool ) );
		
		cout
			<< sample_id[ pid[0] ] << '\t'
			<< sample_id[ pid[1] ] << '\t'
			<< marker_id[ sid[0] ].chr << '\t'
			<< marker_id[ sid[0] ].bp_distance << ' '
			<< marker_id[ sid[1] ].bp_distance << '\t'
			<< marker_id[ sid[0] ].rsid << ' '
			<< marker_id[ sid[1] ].rsid << '\t'
			<< (sid[1] - sid[0] + 1) << '\t'
			<< setiosflags(ios::fixed) << setprecision(2)
			<< get_distance( marker_id[sid[0]] , marker_id[sid[1]] , genetic ) << '\t';
		
		if ( genetic ) cout << "cM\t"; else cout << "MB\t";
		cout << dif << '\t';
		if ( hom[0] ) cout << "1\t"; else cout << "0\t";
		if ( hom[1] ) cout << "1\t"; else cout << "0\t";
		cout << endl;
	}
	file_bmatch.close();
}
