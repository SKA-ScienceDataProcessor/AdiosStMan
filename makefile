ifeq ($(VENDOR),cray)
	CC=cc -dynamic
else
	CC=mpic++
endif

DIRS=benchmark tests
TARGET=libadiosstman.so
SRC=AdiosStMan.cc AdiosStManColumn.cc AdiosStManScaColumn.cc AdiosStManDirColumn.cc AdiosStManIndColumn.cc

$(TARGET):$(SRC)
	$(CC) $(SRC) -fPIC -std=c++11 --shared -o $(TARGET) -lcasa_tables -lcasa_casa -ladios -lz
	for d in $(DIRS); do(cd $$d; rm -f $(TARGET); ln -sf ../$(TARGET) ./);  done
ifdef CASA_LIB
	cp $(TARGET) $(CASA_LIB)
endif
ifdef CASA_INC
	cp *.h $(CASA_INC)/casacore/tables/DataMan
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

