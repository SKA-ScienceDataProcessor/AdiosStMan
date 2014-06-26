all:
	c++ simple_test.cc AdiosStMan.cc -o test -lcasa_tables -lcasa_casa

clean:
	rm -rf test *.data

