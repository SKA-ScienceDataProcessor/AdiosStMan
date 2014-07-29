all: clean
	mpic++ -g simple_test.cc AdiosStMan.cc AdiosStManColumn.cc -o test -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz
#	mpic++ simple_test.cc -o test -lcasa_tables -lcasa_casa

clean:
	rm -rf test *.data *.dSYM

