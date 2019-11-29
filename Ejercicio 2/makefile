all: ejercicio2 clean

ejercicio2: main.h main.c validateParams.o archivos.o definiciones.h colaDinamica.o
	gcc -g -o ejercicio2 main.c archivos.o validateParams.o colaDinamica.o -lpthread

validateParams.o: validateParams.c validateParams.h
	gcc -g -o validateParams.o -c validateParams.c

archivos.o: archivos.c definiciones.h
	gcc -g -o archivos.o -c archivos.c

colaDinamica.o: colaDinamica.c colaDinamica.h
	gcc -g -o colaDinamica.o -c colaDinamica.c

clean:
	rm -rf *.o
