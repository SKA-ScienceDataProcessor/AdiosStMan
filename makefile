DIRS=tools benchmark examples
TARGET=libadiosstman.so
SRC=AdiosStMan.cc AdiosStManColumn.cc AdiosStManColumnA.cc


all:$(TARGET) 
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../libadiosstman.so ./; make);  done

$(TARGET):$(SRC) 
	mpic++ $(SRC) -fPIC --shared -o libadiosstman.so -lcasa_tables -lcasa_casa -ladios -lmxml -lz 
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../libadiosstman.so ./);  done

re:clean $(TARGET)

ln:$(TARGET)
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../libadiosstman.so ./);  done


clean:
	rm -rf *.so 
	for d in $(DIRS); do( cd $$d; make clean);  done

