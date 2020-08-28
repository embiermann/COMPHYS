OFILES=main.o parse.o add.o print.o

plus:plus.o libPlus.a
        g++ -o $@ @< -L. -lPlus

libMain.a:$(OFILES)
        ar rc $@ @?

clean:
        rm -f *.a *.o plus
