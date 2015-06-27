ifeq ($(VENDOR),cray)
	CC=cc -dynamic
else
	CC=mpic++
endif

DIRS=tools benchmark examples
TARGET=libadiosstman.so
SRC=AdiosStMan.cc AdiosStManColumn.cc AdiosStManColumnA.cc AdiosStManColumnV.cc


$(TARGET):$(SRC) 
	$(CC) $(SRC) -fPIC --shared -o $(TARGET) -lcasa_tables -lcasa_casa -ladios -lmxml -lz 
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../$(TARGET) ./);  done
ifdef CASA_LIB
	cp $(TARGET) $(CASA_LIB)
endif

all:$(TARGET) 
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../$(TARGET) ./; make);  done

re:cl $(TARGET)
	

ln:$(TARGET)
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../$(TARGET) ./);  done

cl:
	rm -f *.so

clean:
	rm -rf *.so 
	for d in $(DIRS); do( cd $$d; make clean);  done

