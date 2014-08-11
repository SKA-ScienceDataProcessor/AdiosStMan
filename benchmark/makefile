CC = mpic++
CCFLAGS = 
LDFLAGS = -lcasa_tables -lcasa_casa -ladios -lhdf5 -lmxml -lz

STMANCCFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc

TARGET = serial_array

$(TARGET): $(TARGET).cc
	$(CC) $(CFLAGS) $(LDFLAGS) $(STMANCCFILES) $(TARGET).cc -o bench_$(TARGET) 


all: cl $(TARGET)

cl:
	rm -rf *.casa *.png *.e* *.o*

clean:cl
	rm -rf bench_* *.dSYM 
