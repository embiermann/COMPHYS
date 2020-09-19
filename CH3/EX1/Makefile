CXXFLAGS= $(shell pkg-config --cflags eigen3)

ppVol:ppVol.o
	c++ $(CXXFLAGS) -o $@ $< 

clean:
	rm -f *.a *.o ppVol *~
