DIRS = tools benchmark examples


all: 
	mpic++ AdiosStMan.cc AdiosStManColumn.cc -fPIC --shared -o libadiosstman.so -lcasa_tables -lcasa_casa -ladios -lmxml -lz

clean:
	rm -rf *.so 
	for d in $(DIRS); do( cd $$d; make clean);  done

