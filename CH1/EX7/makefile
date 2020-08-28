OFILES=parse.o add.o print.o

plus:main.o libPlus.so
	c++ -shared -fPIC -o $@ $< -L. -lPlus

libPlus.so:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.so *.o plus *~
