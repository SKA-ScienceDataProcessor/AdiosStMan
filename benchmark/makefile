CC = mpic++
CCFLAGS = 
LDFLAGS = -ladios -lcasa_tables -lcasa_casa -lhdf5 -lmxml -lz

STMANCCFILES = ../AdiosStMan.cc ../AdiosStManColumn.cc

TARGET = serial_array

$(TARGET): $(TARGET).cc
	$(CC) $(STMANCCFILES) $(TARGET).cc -o bench_$(TARGET) $(CFLAGS) $(LDFLAGS) 


all: cl $(TARGET)

cl:
	rm -rf *.casa *.png *.e* *.o* *.log

clean:cl
	rm -rf bench_* *.dSYM 
