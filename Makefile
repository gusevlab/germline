CXX = g++
INCLUDES = include
CXXFLAGS = -O3 -Wall -I $(INCLUDES)
OBJECTS = GERMLINE_0001.o GERMLINE.o Chromosome.o Share.o ChromosomePair.o HMIndividualsExtractor.o MarkerSet.o Individual.o Individuals.o InputManager.o MatchFactory.o MatchesBuilder.o NucleotideMap.o PEDIndividualsExtractor.o Match.o PolymorphicIndividualsExtractor.o SNP.o SNPPositionMap.o SNPs.o

.PHONY: all
all: germline bmatch impute_to_ped test

bmatch:
	$(CXX) parse_bmatch.cpp -o parse_bmatch

germline: $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^

impute_to_ped:
	$(CXX) impute_to_ped.cpp -o bin/impute_to_ped

test: test_plink

test_plink:
	-@rm -f test/generated.match test/generated.log test/generated.err test/generated.out
	-@./germline -silent -bits 50 -min_m 1 -err_hom 2 -err_het 0 < test/test.run > test/generated.out 2> test/generated.err | echo -e "---\nRunning Test Case\n---"
	diff -q -s test/expected.match test/generated.match

.PHONY: clean
clean:
	-rm -f *.o germline parse_bmatch test/generated.match test/generated.log test/generated.err test/generated.out bin/germline bin/impute_to_ped

