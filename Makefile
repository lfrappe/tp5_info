all: main.exe

calcul.o: calcul.c calcul.h libmat.h
	gcc -c calcul.c

ef.o: ef.c ef.h calcul.h
	gcc -c ef.c

libcalcul.a: calcul.o
	ar cr libcalcul.a calcul.o
	ranlib libcalcul.a

libef.a: ef.o
	ar cr libef.a ef.o
	ranlib libef.a

main.exe: main.c libcalcul.a libef.a libmat.a
	gcc -o main.exe main.c -L. -lcalcul libmat.a -lef -lm -no-pie

clean:
	rm -rf *.o *.a main.exe
