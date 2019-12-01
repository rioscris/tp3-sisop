#include "threadOper.h"

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