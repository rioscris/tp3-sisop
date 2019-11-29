/*
Trabajo Practico Grupal line 3 - Ejercicio 2
Tercera entrega

Integrantes:
Rios Cristian - DNI 40.015.557
Riveros Christian - DNI 37.932.808
Villca Luis - DNI 35.277.730
Nuñez Diego - DNI 36.159.969
*/

#include "main.h"

void calcularThreads(const int threads, const int nLineas, int* nThreads, int* cargaPThread, int* cargaPProcess);

FILE* filesrc;
FILE* filedst;

void *threadCalc(void* param){
    printf("Hello from thread!\n");
    tColaCalc* pColaCalc = (tColaCalc*) param;
    tInfoCalc* pinfoCalc = (tInfoCalc*) malloc(sizeof(tInfoCalc));
    pinfoCalc->primero = 1.0;
    pinfoCalc->segundo = 5.0;
    ponerEnColaCalc(pColaCalc, pinfoCalc);
    // sacarDeColaCalc(pColaCalc, pinfoCalc);
    // printf("Valores almacenados: %f %f\n", pinfoCalc->primero, pinfoCalc->segundo);
    pthread_exit((void*)pColaCalc);
}

int main(int argc, char *argv[]) {
    char line[LINE_LEN], *aux;
    char fileIn[PATH_LEN];
    char fileOut[PATH_LEN];
    double resultado;
    int threads = 0;
    int nLineas = 0;
    int nThreads = 0;
    int cargaPThread = 0;
    int cargaPProcess = 0;
    int iThread;
    int iCargaThread;

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

    rewind(filesrc);
    rewind(filedst);

    pthread_t thread_id;
    tColaThread colaThreads;
    tColaCalc* auxColaCalc;
    tInfoCalc* auxInfoCalc;
    tInfoThread* auxInfoThread;
    crearColaThread(&colaThreads);

    // int var = 1;
    // int *auxVar = &var;
    // pthread_create(&thread_id, NULL, threadCalc, auxVar);
    // pthread_join(thread_id, (void**)&(auxVar));
    // printf("Recibido desde el thread %d\n", var);
    
    for (int i = 0; i < nThreads; i++)
    {
        auxColaCalc = (tColaCalc*) malloc(sizeof(tColaCalc));
        crearColaCalc(auxColaCalc);
        
        auxInfoThread = (tInfoThread*) malloc(sizeof(tInfoThread));
        pthread_create(&(auxInfoThread->thread_id), NULL, threadCalc, auxColaCalc);
        ponerEnColaThread(&colaThreads, auxInfoThread);
    }

    for (int i = 0; i < nThreads; i++)
    {
        sacarDeColaThread(&colaThreads, &auxInfoThread);
        pthread_join(auxInfoThread->thread_id, (void**)&(auxColaCalc));
        sacarDeColaCalc(auxColaCalc, &auxInfoCalc);
        printf("Thread n# %d retorno cola con primer items: %f y %f\n", i, auxInfoCalc->primero, auxInfoCalc->segundo);
        free(auxInfoCalc);
        free(auxColaCalc);
        printf("puntero vale %p\n", auxInfoThread);
        free(auxInfoThread);
    }

    // Carga de trabajo a los threads

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
