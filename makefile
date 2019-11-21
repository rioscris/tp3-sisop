all: ejercicio3 clean

ejercicio3: main.h main.c demonio.o fifos.o log.o stringExt.o ayuda.o
	gcc -o ejercicio3 main.c demonio.o fifos.o log.o stringExt.o ayuda.o

demonio.o: demonio.h demonio.c
	gcc -o demonio.o -c demonio.c

log.o: log.c log.h
	gcc -o log.o -c log.c 

stringExt.o: stringExt.c stringExt.h
	gcc -o stringExt.o -c stringExt.c

ayuda.o: ayuda.c ayuda.h
	gcc -o ayuda.o -c ayuda.c

clean:
	rm -rf *.o