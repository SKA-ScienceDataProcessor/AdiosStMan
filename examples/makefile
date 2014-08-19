CC = mpic++
CCFLAGS = 
LDFLAGS = -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES = libadiosstman.so
TARGET = wAdiosStMan rAdiosStMan wAdiosStManMPI

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc} ${STMANFILES}
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

${STMANFILES}:  
	cd ..; make; mv *.so examples 

cl:
	rm -rf *.casa 

clean:cl
	rm -rf ${TARGET} *.dSYM *.so

re: clean all
