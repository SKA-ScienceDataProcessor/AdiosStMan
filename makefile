all: clean
	mpic++ AdiosStMan.cc AdiosStManColumn.cc --shared -o libAdiosStMan.so -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz

clean:
	rm -rf *.so 

