IDIR=/usr/include/eigen3
CFLAGS=-I$(IDIR)

ppVol:ppVol.o
	c++ -o $@ $< 

clean:
	rm -f *.a *.o ppVol *~
