#include "GERMLINE.h"
#include <string.h>

double MIN_MATCH_LEN = 3;
int MARKER_SET_SIZE = 128;
bool PRINT_MATCH_HAPS = false;
bool ROI = false;
bool HAP_EXT = true;
bool WIN_EXT = false;
bool ALLOW_HOM = false;
bool HOM_ONLY = false;
bool HAPLOID = false;
bool SILENT = false;
bool DEBUG = false;
bool BINARY_OUT = false;
bool MINIMAL_OUT = false;
bool DISTRIB_OUT = false;
int MAX_ERR_HOM = 1;
int MAX_ERR_HET = 0;
string ped_file = "";
string map_file = "";
string out_file = "";

vector< int > hist_ctr;
vector< float > hist_win;

// main(): runs GERMLINE
int main(int argc, char* argv[])
{
	// parse arguments
	string rs_range[2] , map , hist; hist = map = rs_range[0] = rs_range[1] = "";
	string params = argv[0];

	bool bad_param = false;
	for(int i=1;i<argc;i++){
		params += " " + string(argv[i]);
		if( strncmp(argv[i], "-min_m", strlen("-min_m")) == 0 && i < argc-1)				MIN_MATCH_LEN = atof(argv[++i]);
		else if( strncmp(argv[i], "-err_hom", strlen("-max_err")) == 0 && i < argc-1)		{ MAX_ERR_HOM = atoi(argv[++i]); }
		else if( strncmp(argv[i], "-err_het", strlen("-max_err")) == 0 && i < argc-1)		{ MAX_ERR_HET = atoi(argv[++i]); }
		else if( strncmp(argv[i], "-from_snp", strlen("-from_snp")) == 0 && i < argc-1 )	rs_range[0] = argv[++i];
		else if( strncmp(argv[i], "-to_snp", strlen("-to_snp")) == 0 && i < argc-1 )		rs_range[1] = argv[++i];
		else if( strncmp(argv[i], "-print", strlen("-print")) == 0 )						PRINT_MATCH_HAPS = true;
		else if( strncmp(argv[i], "-silent", strlen("-silent")) == 0 )						SILENT = true;
		else if( strncmp(argv[i], "-debug", strlen("-debug")) == 0 )						DEBUG = true;
		else if( strncmp(argv[i], "-input", strlen("-input")) == 0 && i < argc-2)				{ ped_file = argv[++i]; map_file = argv[++i];  }
		else if( strncmp(argv[i], "-output", strlen("-output")) == 0 && i < argc-1)				{ out_file = argv[++i];  }
		else if( strncmp(argv[i], "-map", strlen("-map")) == 0 && i < argc-1)				map_file = argv[++i];
		else if( strncmp(argv[i], "-bits", strlen("-bits")) == 0 && i < argc-1)				MARKER_SET_SIZE = atoi(argv[++i]);
		else if( strncmp(argv[i], "-homoz-only", strlen("-homoz-only")) == 0 )				{ ALLOW_HOM = true; HOM_ONLY = true; }
		else if( strncmp(argv[i], "-homoz", strlen("-homoz")) == 0 )						ALLOW_HOM = true;
		else if( strncmp(argv[i], "-bin_out", strlen("-bin_out")) == 0 )						BINARY_OUT = true;
		else if( strncmp(argv[i], "-min_out", strlen("-min_out")) == 0 )						MINIMAL_OUT = true;
		else if( strncmp(argv[i], "-haploid", strlen("-haploid")) == 0 )					{ HAPLOID = true; HAP_EXT = true; }
		else if( strncmp(argv[i], "-h_extend", strlen("-h_extend")) == 0 )					HAP_EXT = true;
		else if( strncmp(argv[i], "-g_extend", strlen("-h_extend")) == 0 )					HAP_EXT = false;
		else if( strncmp(argv[i], "-w_extend", strlen("-w_extend")) == 0 )					WIN_EXT = true;
		else if( strncmp(argv[i], "-distrib", strlen("-distrib")) == 0 )					{ DISTRIB_OUT = true; hist = argv[++i]; }
		else bad_param = true;
	}

	if(MIN_MATCH_LEN < 0)
	{
		cerr << "ERROR: -min_m must be non-negative" << endl << endl;
		bad_param = true;
	} else if(MAX_ERR_HOM < 0 || MAX_ERR_HET < 0 )
	{
		cerr << "ERROR: -err_hom,-err_het must be non-negative" << endl << endl;
		bad_param = true;
	} else if(HAPLOID && ALLOW_HOM)
	{
		cerr << "ERROR: cannot execute with both -haploid and -homoz/-homoz-only flags active" << endl << endl;
		bad_param = true;
	}
	
	if(bad_param)
	{
		cerr << "usage: " << argv[0] << "<flags (optional)> -input [ped file] [map file] -output [out file]" << endl
		<< "flags:" << endl
		<< '\t' << "-silent" << '\t' << "Suppress all output except for warnings and prompts." << endl
		<< '\t' << "-input" << '\t' << "[ped] and [map] inputs (*required for non-interactive*)" << endl
		<< '\t' << "-output" << '\t' << "output prefix (*required for non-interactive*)" << endl
		<< '\t' << "-min_m" << '\t' << "Minimum length for match to be used for imputation (in cM or MB)." << endl
		<< '\t' << "-err_hom" << '\t' << "Maximum number of mismatching homozygous markers (per slice)." << endl
		<< '\t' << "-err_het" << '\t' << "Maximum number of mismatching heterozygous markers (per slice)." << endl
		<< '\t' << "-from_snp" << '\t' << "Start SNP (rsID)." << endl
		<< '\t' << "-to_snp" << '\t' << "End SNP (rsID)." << endl
		<< '\t' << "-haps" << '\t' << "Print the resolved haplotypes in a seperate HAPS file." << endl
		<< '\t' << "-map [file]" << '\t' << "Genetic distance map in PLINK map format." << endl
		<< '\t' << "-distrib [file]" << '\t' << "Only print the distribution of segment lengths, using breaks listed in file." << endl		
		<< '\t' << "-bits" << '\t' << "Slice size." << endl
		<< '\t' << "-homoz" << '\t' << "Allow self matches (homozygosity)" << endl
		<< '\t' << "-homoz-only" << '\t' << "Look for autozygous/homozygous segments only, does not detect IBD" << endl
		<< '\t' << "-haploid" << '\t' << "Treat input individual as two fully phased chromosomes with no recombination\n\t\toutput IDs with 0/1 suffix for chromosome destinction" << endl
		<< '\t' << "-h_extend" << '\t' << "Extend from seeds if *haplotypes* match" << endl
		<< '\t' << "-w_extend" << '\t' << "Extend, one marker at a time, beyong the boundaries of a found match" << endl;
		return 0;
	}

	if( rs_range[0] != "" && rs_range[1] != "" )
	{
		ROI = true;
		ALL_SNPS.setROI(rs_range);
	}

	if(map != "")
	{
		ALL_SNPS.loadGeneticDistanceMap( map );
	}
	
	if(DISTRIB_OUT) {
		// load the histogram
       	ifstream s_map( hist.c_str() );
        if(!s_map) { cerr << "WARNING: Histogram for distributions \"" << hist << "\" could not be loaded" << endl; return -1; }
        float d;
        while(s_map >> d && s_map.good())
       	{
			hist_win.push_back( d );
			hist_ctr.push_back( 0 );
        }
	cerr << "Loaded " << hist_win.size() << " distribution breaks" << endl;
	}

	GERMLINE germline;
    germline.mine( params );
    return 1;
}


// end GERMLINE_0001.cpp
