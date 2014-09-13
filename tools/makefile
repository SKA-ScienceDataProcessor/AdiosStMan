CC = mpic++
CCFLAGS = -g
LDFLAGS = -lcasa_tables -lcasa_casa
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES=libadiosstman.so
TARGET=ms_converter ms_checker

all: ${TARGET} cl

${TARGET}: ${TARGET:=.cc} ${STMANFILES}
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

${STMANFILES}:  
	cd ..; make ln; 

cl:
	rm -rf *.casa *.e* *.o*

clean:cl
	rm -rf ${TARGET} *.dSYM *.so

re: clean all
