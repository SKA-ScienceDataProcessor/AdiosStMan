CC = mpic++
CCFLAGS = -g
LDFLAGS = -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES = -lAdiosStMan
TARGET = wAdiosStMan rAdiosStMan wAdiosStManMPI

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc} libAdiosStMan.so
	$(CC) $(STMANFILES) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) 

libAdiosStMan.so:  
	cd ..; make; mv *.so examples 

cl:
	rm -rf *.casa 

clean:cl
	rm -rf ${TARGET} *.dSYM *.so

re: clean all
