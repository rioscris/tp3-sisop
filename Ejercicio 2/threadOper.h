#include <stdio.h>
#include <string.h>
#include "colaDinamica.h"
#include "archivos.h"
#include "operations.h"

int cargaPThread = 0;

void calcularThreads(const int threads, const int nLineas, int* nThreads, int* cargaPThread, int* cargaPProcess);
int cargaEnThreads(FILE* filesrc, tColaThread* colaThreads, const int nThreads, const int cargaPThread);
int descargaThreadsEnArchivo(FILE* filedst, tColaThread* colaThreads, const int nThreads, const int cargaPThread);