ifeq ($(VENDOR),cray)
	CC=cc -dynamic
else
	CC=mpic++
endif

CCFLAGS=-std=c++11
LDFLAGS=-ladios -lcasa_tables -lcasa_casa -lmxml
STMANFILES=libadiosstman.so
TARGET=serial_array_write \
	   parallel_array_write \
	   ms_read_column

all: $(TARGET) cl

$(TARGET): $(TARGET:=.cc) $(STMANFILES)
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES)

$(STMANFILES):
	cd ..; make ln;

cl:
	rm -rf *.casa *.eps *.e* *.o* *.log *.ER *.OU

clean:cl
	rm -rf $(TARGET) *.dSYM *.so log

re: clean all
