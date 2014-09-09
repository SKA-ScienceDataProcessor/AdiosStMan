CC = mpic++
CCFLAGS = -g
LDFLAGS = -lcasa_tables -lcasa_casa
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES=libadiosstman.so
TARGET=mwa_converter mwa_checker

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc} ${STMANFILES}
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

${STMANFILES}:  
	cd ..; make; cp *.so tools

cl:
	rm -rf *.casa *.e* *.o*

clean:cl
	rm -rf ${TARGET} *.dSYM *.so

re: clean all
