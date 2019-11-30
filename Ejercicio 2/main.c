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
int cargaEnThreads(FILE* filesrc, tColaThread* colaThreads, const int nThreads, const int cargaPThread);
int descargaThreadsEnArchivo(FILE* filedst, tColaThread* colaThreads, const int nThreads, const int cargaPThread);
int calcularRestantesEnProceso(FILE* filesrc, FILE* filedst, const int cargaPProcess);

FILE* filesrc;
FILE* filedst;
int cargaPThread = 0;    

void calcular(tInfoCalc* pInfoCalc){
    pInfoCalc->resultado = pInfoCalc->primero + pInfoCalc->segundo;
}

void *threadCalc(void* param){
    tColaCalc* pColaCalc = (tColaCalc*) param;
    tInfoCalc* pInfoCalc = NULL;
    for (int i = 0; i < cargaPThread; i++)
    {
        sacarDeColaCalc(pColaCalc, &pInfoCalc);
        calcular(pInfoCalc);
        ponerEnColaCalc(pColaCalc, pInfoCalc);
    }
    pthread_exit((void*)pColaCalc);
}

int main(int argc, char *argv[]) {
    char line[LINE_LEN];
    char fileIn[PATH_LEN];
    char fileOut[PATH_LEN];
    int threads = 0;
    int nLineas = 0;
    int nThreads = 0;
    int cargaPProcess = 0;

    validateParams(argc, argv, &threads, fileIn, fileOut);
    
    printf("Archivo de entrada: %s\n", fileIn);
    printf("Archivo de saslida: %s\n", fileOut);

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

int cargaEnThreads(FILE* filesrc, tColaThread* colaThreads, const int nThreads, const int cargaPThread){
    rewind(filesrc);

    tInfoThread* auxInfoThread;
    tColaCalc* auxColaCalc;
    tInfoCalc* auxInfoCalc;
    char line[LINE_LEN];
    t_par auxPar;

    for (int i = 0; i < nThreads; i++)
    {
        auxInfoThread = (tInfoThread*) malloc(sizeof(tInfoThread));

        auxColaCalc = (tColaCalc*) malloc(sizeof(tColaCalc));
        crearColaCalc(auxColaCalc);
        
        for (int j = 0; j < cargaPThread; j++)
        {
            auxInfoCalc = (tInfoCalc*) malloc(sizeof(tInfoCalc));
            
            if(!fgets(line, sizeof(line), filesrc))
                return THREAD_LOAD_ERROR;
            
            trozarCampos(&auxPar, line);
            auxInfoCalc->primero = auxPar.primero;
            auxInfoCalc->segundo = auxPar.segundo;

            ponerEnColaCalc(auxColaCalc, auxInfoCalc);
        }

        pthread_create(&(auxInfoThread->thread_id), NULL, threadCalc, auxColaCalc);

        ponerEnColaThread(colaThreads, auxInfoThread);
    }

    return OP_SUCESS;
}

int descargaThreadsEnArchivo(FILE* filedst, tColaThread* colaThreads, const int nThreads, const int cargaPThread){
    rewind(filedst);
    tInfoThread* auxInfoThread;
    tColaCalc* auxColaCalc;
    tInfoCalc* auxInfoCalc;
    
    for (int i = 0; i < nThreads; i++)
    {
        sacarDeColaThread(colaThreads, &auxInfoThread);
        pthread_join(auxInfoThread->thread_id, (void**)&(auxColaCalc));

        for (int j = 0; j < cargaPThread; j++)
        {
            sacarDeColaCalc(auxColaCalc, &auxInfoCalc);
            // printf("Recibido del thread n# %d el resultado %f\n", i+1, auxInfoCalc->resultado);
            if(fprintf(filedst, "%f\n", auxInfoCalc->resultado) < 0)
                return THREAD_DOWNLOAD_ERROR;
            
            free(auxInfoCalc);
        }

        free(auxColaCalc);
        free(auxInfoThread);
    }

    return OP_SUCESS;
}

int calcularRestantesEnProceso(FILE* filesrc, FILE* filedst, const int cargaPProcess){
    t_par auxPar;
    char line[LINE_LEN];
    tInfoCalc auxInfoCalcProcess;
    
    for (int i = 0; i < cargaPProcess; i++)
    {
        if(!fgets(line, sizeof(line), filesrc))
            return REMAINING_CALC_ERROR;
        
        trozarCampos(&auxPar, line);
        auxInfoCalcProcess.primero = auxPar.primero;
        auxInfoCalcProcess.segundo = auxPar.segundo;
        calcular(&auxInfoCalcProcess);
        // printf("Desde el proceso, escribiendo el resultado %f\n", auxInfoCalcProcess.resultado);
        if(fprintf(filedst, "%f\n", auxInfoCalcProcess.resultado) < 0)
            return REMAINING_CALC_ERROR;
    }

    return OP_SUCESS;
}

void calcularThreads(const int threads, const int lineas, int* nThreads, int* cargaPThread, int* cargaPProcess){
    printf("Cantidad de lineas en archivo %d\n", lineas);
    
    *nThreads = (threads > 0 && lineas >= threads) ? threads : 0;

    printf("Numero de threads necesitados: %d\n", *nThreads);
    if(*nThreads != 0){
        *cargaPThread = lineas / threads;
    }
    printf("Carga de cuentas por thread: %d\n", *cargaPThread);
    if(*cargaPThread * *nThreads < lineas){
        *cargaPProcess = lineas - *cargaPThread * *nThreads;
        printf("Cuentas restantes a realizar por el proceso: %d\n", *cargaPProcess);
    }
}
