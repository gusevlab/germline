GERMLINE
--------

*GERMLINE is an algorithm to infer long shared segments of Identity by Descent (IBD) between pairs of individuals in a large population. GERMLINE is very fast.*

GERMLINE takes as input ([PLINK](https://www.cog-genomics.org/plink/1.9/) format) haplotype marker data for individuals and generates a list of all pairwise segmental sharing.

* To compile GERMLINE run `make` in the download directory, or use the precompiled binary in `bin/germline`.
* To run GERMLINE use: `germline -input [ped] [map] -output [out]`.
* See [http://gusevlab.org/projects/germline/](http://gusevlab.org/projects/germline/) for full documentation.

GERMLINE was developed in Itsik Pe'er's Lab of Computational Genetics at Columbia University. If you use GERMLINE in a published analysis, please cite `Gusev et al. 2008 Genome Res doi: 10.1101/gr.081398.108`.

GERMLINE is licensed under Apache.
