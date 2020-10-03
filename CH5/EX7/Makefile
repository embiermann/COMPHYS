CXXFLAGS= $(shell pkg-config --cflags eigen3) -O0 -g -gdwarf-2

OFILES=integral.o Phin.o phiMatrix.o

EX7:EX7.o libEX7.a
	c++ $(CXXFLAGS) -o $@ $< -L. -lEX7 -lQatGenericFunctions

libEX7.a:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.a *.o EX7 *~
