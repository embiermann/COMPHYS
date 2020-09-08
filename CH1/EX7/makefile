OFILES=parse.o add.o print.o
CXXFLAGS = -fPIC 
plus:main.o libPlus.so
	c++  -fPIC -o $@ $< -L. -lPlus

libPlus.so:$(OFILES)
	c++ -shared -o  $@ $?

clean:
	rm -f *.so *.o plus *~
