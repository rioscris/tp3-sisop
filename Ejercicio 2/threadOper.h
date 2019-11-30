#include <stdio.h>
#include <string.h>
#include "colaDinamica.h"
#include "archivos.h"
#include "operations.h"
// #include "global.h"

extern int cargaPThread;

void calcularThreads(const int threads, const int nLineas, int* nThreads, int* cargaPThread, int* cargaPProcess);
int cargaEnThreads(FILE* filesrc, tColaThread* colaThreads, const int nThreads, const int cargaPThread);
int descargaThreadsEnArchivo(FILE* filedst, tColaThread* colaThreads, const int nThreads, const int cargaPThread);