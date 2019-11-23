all: ejercicio3 clean

ejercicio3: main.h main.c demonio.o ipc.o log.o stringExt.o ayuda.o articulosFunc.o filtro.o
	gcc -o ejercicio3 main.c demonio.o ipc.o log.o stringExt.o ayuda.o articulosFunc.o filtro.o

demonio.o: demonio.h demonio.c
	gcc -o demonio.o -c demonio.c

log.o: log.c log.h
	gcc -o log.o -c log.c 

stringExt.o: stringExt.c stringExt.h
	gcc -o stringExt.o -c stringExt.c

articulosFunc.o: articulosFunc.c articulosFunc.h stringExt.o filtro.o
	gcc -o articulosFunc.o -c articulosFunc.c

ayuda.o: ayuda.c ayuda.h
	gcc -o ayuda.o -c ayuda.c

ipc.o: ipc.c log.o articulosFunc.o filtro.o articulosFunc.o
	gcc -o ipc.o -c ipc.c

filtro.o: filtro.c filtro.h tipos.h stringExt.o
	gcc -o filtro.o -c filtro.c

clean:
	rm -rf *.o