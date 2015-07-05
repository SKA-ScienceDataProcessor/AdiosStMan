ifeq ($(VENDOR),cray)
	CC=cc -dynamic
else
	CC=mpic++
endif

CCFLAGS=
LDFLAGS=-lcasa_tables -lcasa_casa 
STMANFILES=libadiosstman.so
TARGET=writeScalar writeDirArr writeFixArr writeArbArr writeMPI read readScalar readSlice

all: $(TARGET) cl

$(TARGET): $(TARGET:=.cc) $(STMANFILES)
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

$(STMANFILES):  
	cd ..; make ln;

cl:
	rm -rf *.casa 

clean:cl
	rm -rf $(TARGET) *.dSYM *.so

re: clean all
