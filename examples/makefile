CC = mpic++
CCFLAGS = -g
LDFLAGS = -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz
STMANCCFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
TARGET = tAdiosStMan tAdiosStManMPI

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc}
	$(CC) $(CCFLAGS) $(LDFLAGS) $(STMANCCFILES) $@.cc -o $@

cl:
	rm -rf *.casa 

clean:cl
	rm -rf ${TARGET} *.dSYM 
