all: ejercicio2 clean

ejercicio2: main.h main.c validateParams.o archivos.o definiciones.h colaDinamica.o operations.o threadOper.o processOper.o 
	gcc -g -o ejercicio2 main.c archivos.o validateParams.o colaDinamica.o operations.o threadOper.o  processOper.o -lpthread

validateParams.o: validateParams.c validateParams.h
	gcc -g -o validateParams.o -c validateParams.c

archivos.o: archivos.c
	gcc -g -o archivos.o -c archivos.c

colaDinamica.o: colaDinamica.c colaDinamica.h
	gcc -g -o colaDinamica.o -c colaDinamica.c

operations.o: operations.c operations.h colaDinamica.o
	gcc -g -o operations.o -c operations.c 

processOper.o: processOper.c processOper.h
	gcc -g -o processOper.o -c processOper.c

threadOper.o: threadOper.c threadOper.h colaDinamica.o archivos.o operations.o
	gcc -g -o threadOper.o -c threadOper.c

clean:
	rm -rf *.o
