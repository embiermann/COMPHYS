CXXFLAGS= $(shell pkg-config --cflags eigen3)

PWBARRIER:pwbarrier.o
	c++ $(CXXFLAGS) -o $@ $< 

clean:
	rm -f *.a *.o PWBARRIER *~
