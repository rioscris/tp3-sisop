all: ejercicio3 clean

ejercicio3: main.h main.c demonio.o ipc.o log.o stringExt.o ayuda.o articulosFunc.o filtro.o validParams.o
	gcc -g -o ejercicio3 main.c demonio.o ipc.o log.o stringExt.o ayuda.o articulosFunc.o filtro.o validParams.o

demonio.o: demonio.h demonio.c
	gcc -g -o demonio.o -c demonio.c

log.o: log.c log.h
	gcc -g -o log.o -c log.c 

stringExt.o: stringExt.c stringExt.h
	gcc -g -o stringExt.o -c stringExt.c

articulosFunc.o: articulosFunc.c articulosFunc.h stringExt.o filtro.o
	gcc -g -o articulosFunc.o -c articulosFunc.c

ayuda.o: ayuda.c ayuda.h
	gcc -g -o ayuda.o -c ayuda.c

validParams.o: validParams.c validParams.h ayuda.o
	gcc -g -o validParams.o -c validParams.c

ipc.o: ipc.c log.o articulosFunc.o filtro.o articulosFunc.o
	gcc -g -o ipc.o -c ipc.c

filtro.o: filtro.c filtro.h tipos.h stringExt.o
	gcc -g -o filtro.o -c filtro.c

clean:
	rm -rf *.o
