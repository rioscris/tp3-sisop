all: ejercicio2 clean

ejercicio2: main.h main.c validateParams.o archivos.o definiciones.h
	gcc -g -o ejercicio2 main.c archivos.o validateParams.o

validateParams.o: validateParams.c validateParams.h
	gcc -g -o validateParams.o -c validateParams.c

archivos.o: archivos.c definiciones.h
	gcc -g -o archivos.o -c archivos.c

clean:
	rm -rf *.o
