ppVol:ppVol.o libPpVol.a
        c++ -o $@ $< -L. -lPpVol -I/usr/include/eigen3

libPpVol.a:$(OFILES)
        ar rc $@ $?

clean:
        rm -f *.a *.o ppVol *~
