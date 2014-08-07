all: clean
	mpic++  tAdiosStMan.cc ../AdiosStMan.cc ../AdiosStManColumn.cc -o adios -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz
	mpic++  tBench.cc ../AdiosStMan.cc ../AdiosStManColumn.cc -o bench -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz

cl:
	rm -rf *.casa *.png *.e* *.o*

clean:cl
	rm -rf adios bench *.dSYM 
