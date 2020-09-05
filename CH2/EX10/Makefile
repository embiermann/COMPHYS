OFILES=sec3d.o cubicSolver.o

EX10:EX10.o libEX10.a
	c++ -o $@ $< -L. -lEX10

libEX10.a:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.a *.o EX10 *~
