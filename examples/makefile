CC = mpic++
CCFLAGS = -g
LDFLAGS = -lcasa_tables -lcasa_casa 
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES = libadiosstman.so
TARGET = wAdiosStMan wAdiosStManMPI wAdiosStManMPI2 rAdiosStMan rAdiosStManSlice

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc} ${STMANFILES}
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

${STMANFILES}:  
	cd ..; make; cp *.so examples 

cl:
	rm -rf *.casa 

clean:cl
	rm -rf ${TARGET} *.dSYM *.so

re: clean all
