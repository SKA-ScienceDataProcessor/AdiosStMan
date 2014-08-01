all: clean
	mpic++ -g tAdiosStMan.cc AdiosStMan.cc AdiosStManColumn.cc -o adios -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz

clean:
	rm -rf adios *.casa *.dSYM

