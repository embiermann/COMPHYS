OFILES=parse.o add.o print.o

main:main.o libMain.a
	c++ -o $@ $< -L. -lMain

libMain.a:$(OFILES)
	ar rc $@ $?

clean:
	rm -f *.a *.o main *~
