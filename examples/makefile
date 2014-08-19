CC = mpic++
CCFLAGS = 
LDFLAGS = -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES = libAdiosStMan.so
TARGET = wAdiosStMan rAdiosStMan wAdiosStManMPI

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc} libAdiosStMan.so
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

libAdiosStMan.so:  
	cd ..; make; mv *.so examples 

cl:
	rm -rf *.casa 

clean:cl
	rm -rf ${TARGET} *.dSYM *.so

re: clean all
