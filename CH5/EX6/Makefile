CXXFLAGS= $(shell pkg-config --cflags eigen3) -O0 -g -gdwarf-2

OFILES=Phin.o

orthog:orthog.o libOrthog.a
	c++ $(CXXFLAGS) -o $@ $< -L. -lOrthog -lQatGenericFunctions

libOrthog.a:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.a *.o orthog *~

