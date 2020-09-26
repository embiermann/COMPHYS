CXXFLAGS= $(shell pkg-config --cflags eigen3)

OFILES=Phin.o

orthog:orthog.o libOrthog.a
	c++ $(CXXFLAGS) -o $@ $< -L. -lOrthog

libOrthog.a:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.a *.o orthog *~

