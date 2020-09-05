OFILES=quad.o

EX9:EX9.o libEX9.a
	c++ -o $@ $< -L. -lEX9

libEX9.a:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.a *.o EX9 *~
