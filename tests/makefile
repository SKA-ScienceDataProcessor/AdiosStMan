ifeq ($(VENDOR),cray)
	CC=cc -dynamic
else
	CC=mpic++
endif

CCFLAGS=-std=c++11
LDFLAGS=-lcasa_tables -lcasa_casa
STMANFILES=libadiosstman.so
TARGET=writeScalar \
	   writeDirArr \
	   writeFixArr \
	   writeArbArr \
	   writeMPI \
	   readArr \
	   readArrColumn \
	   readArrColumnSlice \
	   readScalar

all: $(TARGET) cl

$(TARGET): $(TARGET:=.cc) $(STMANFILES)
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES)

$(STMANFILES):
	cd ..; make ln;

cl:
	rm -rf *.casa *.out

clean:cl
	rm -rf $(TARGET) *.dSYM *.so

re: clean all
