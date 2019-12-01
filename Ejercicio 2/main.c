/*
Trabajo Practico Grupal 3 - Ejercicio 2
Tercera entrega

Integrantes:
Rios Cristian - DNI 40.015.557
Riveros Christian - DNI 37.932.808
Villca Luis - DNI 35.277.730
Nuñez Diego - DNI 36.159.969
*/

#include "main.h"

int main(int argc, char *argv[]) {
    char line[LINE_LEN];
    char fileIn[PATH_LEN];
    char fileOut[PATH_LEN];
    FILE* filesrc;
    FILE* filedst;
    int threads = 0;
    int nLineas = 0;
    int nThreads = 0;
    int cargaPProcess = 0;

    validateParams(argc, argv, &threads, fileIn, fileOut);
    
    printf("Archivo de entrada: %s\n", fileIn);
    printf("Archivo de salida: %s\n", fileOut);

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

    tColaThread colaThreads;
    crearColaThread(&colaThreads);

    if (cargaEnThreads(filesrc, &colaThreads, nThreads, cargaPThread) == THREAD_LOAD_ERROR) {
        fprintf(stderr, "Error durante la carga de threads\n");
        fprintf(stderr, "Se ha llegado al fin de archivo antes de lo esperado\n");
        fclose(filesrc);
        fclose(filedst);
        exit(THREAD_LOAD_ERROR);
    }

    if (descargaThreadsEnArchivo(filedst, &colaThreads, nThreads, cargaPThread) == THREAD_DOWNLOAD_ERROR) {
        fprintf(stderr, "Error durante la descarga de threads al archivo\n");
        fclose(filesrc);
        fclose(filedst);
        exit(THREAD_DOWNLOAD_ERROR);
    }

    if (calcularRestantesEnProceso(filesrc, filedst, cargaPProcess) == REMAINING_CALC_ERROR) {
        fprintf(stderr, "Error durante los calculos restantes en el proceso\n");
        fclose(filesrc);
        fclose(filedst);
        exit(REMAINING_CALC_ERROR);
    }
    
    fclose(filesrc);
    fclose(filedst);

    return 0;
}