CC = mpic++
CCFLAGS = 
LDFLAGS = -ladios -lcasa_tables -lcasa_casa
#STMANFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc
STMANFILES = libadiosstman.so
TARGET = serial_array_write serial_array_read_slice parallel_array_write

all: $(TARGET) cl

$(TARGET): $(TARGET:=.cc) $(STMANFILES)
	$(CC) $@.cc -o $@ $(CCFLAGS) $(LDFLAGS) $(STMANFILES) 

${STMANFILES}:  
	cd ..; make; cp *.so benchmark

cl:
	rm -rf *.casa *.png *.e* *.o* *.log

clean:cl
	rm -rf $(TARGET) *.dSYM  *.so log

re: clean all
