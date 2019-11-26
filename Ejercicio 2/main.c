/*
Trabajo Practico Grupal line 3 - Ejercicio 2
Segunda entrega

Integrantes:
Nuñez Diego - DNI 36.159.969
Rios Cristian - DNI 40.015.557
Riveros Christian - DNI 37.932.808
Villca Luis - DNI 35.277.730
*/

#include "main.h"

void calcularThreads(const int threads, const int nLineas, int* nThreads, int* cargaPThread, int* cargaPProcess);

int main(int argc, char *argv[]) {
    char line[LINE_LEN], *aux;
    FILE *filesrc;
    FILE *filedst;
    char fileIn[PATH_LEN];
    char fileOut[PATH_LEN];
    double resultado;
    t_par par;
    int threads = 0;
    int nLineas = 0;
    int nThreads = 0;
    int cargaPThread = 0;
    int cargaPProcess = 0;

    validateParams(argc, argv, &threads, fileIn, fileOut);
    
    printf("%s\n", fileIn);
    printf("%s\n", fileOut);

    if(!abrirArchivo(&filesrc, fileIn,"r")) {
        perror("Error abriendo archivo de datos de vectores. ");
        exit(ON_FILE_ERROR);
    }

    if(!abrirArchivo(&filedst, fileOut,"w")) {
        perror("Error abriendo archivo de escritura de resultados. ");
        exit(ON_FILE_ERROR);
    }

    if( contarLineasEnArchivo(filesrc, &nLineas) == INVALID_DATA){
        fclose(filesrc);
        fclose(filedst);
        fprintf(stderr, "Error: linea numero %d con formato incorrecto.\n", nLineas);
        exit(INVALID_DATA);
    }

    calcularThreads(threads, nLineas, &nThreads, &cargaPThread, &cargaPProcess);

    // while(fgets(line, sizeof(line), filesrc)) {
    //     resultado=0;
        
    //     trozarCampos(&par, line);
    //     resultado = par.primero + par.segundo;
    //     fprintf(filedst, "%lf\n", resultado);
    // }

    fclose(filesrc);
    fclose(filedst);

    return 0;
}

void calcularThreads(const int threads, const int nLineas, int* nThreads, int* cargaPThread, int* cargaPProcess){
    *nThreads = (nLineas > threads && threads != 0) ? threads % nLineas : 0;

    printf("Numero de threads necesitados: %d\n", *nThreads);
    if(*nThreads != 0){
        *cargaPThread = nLineas / *nThreads;
    }
    printf("Carga de cuentas por thread: %d\n", *cargaPThread);
    if(*cargaPThread * *nThreads < nLineas){
        *cargaPProcess = nLineas - *cargaPThread * *nThreads;
        printf("Cuentas restantes a realizar por el proceso: %d\n", *cargaPProcess);
    }
}
