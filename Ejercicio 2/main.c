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
int cargaPThread = 0;    

void calcular(tInfoCalc* pInfoCalc){
    pInfoCalc->resultado = pInfoCalc->primero + pInfoCalc->segundo;
}

void *threadCalc(void* param){
    printf("Hello from thread!\n");
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
    char line[LINE_LEN], *aux;
    char fileIn[PATH_LEN];
    char fileOut[PATH_LEN];
    double resultado;
    int threads = 0;
    int nLineas = 0;
    int nThreads = 0;
    int cargaPProcess = 0;
    int iThread;
    int iCargaThread;
    t_par auxPar;

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

    for (int i = 0; i < nThreads; i++)
    {
        auxColaCalc = (tColaCalc*) malloc(sizeof(tColaCalc));
        crearColaCalc(auxColaCalc);

        auxInfoThread = (tInfoThread*) malloc(sizeof(tInfoThread));
        
        for (int j = 0; j < cargaPThread; j++)
        {
            auxInfoCalc = (tInfoCalc*) malloc(sizeof(tInfoCalc));
            
            if(!fgets(line, sizeof(line), filesrc)){
                fprintf(stderr, "Error durante la carga de threads\n");
                fprintf(stderr, "Se ha llegado al fin de archivo antes de lo esperado\n");
                fclose(filesrc);
                fclose(filedst);
                return -1;
            }
            trozarCampos(&auxPar, line);
            auxInfoCalc->primero = auxPar.primero;
            auxInfoCalc->segundo = auxPar.segundo;

            ponerEnColaCalc(auxColaCalc, auxInfoCalc);
        }

        pthread_create(&(auxInfoThread->thread_id), NULL, threadCalc, auxColaCalc);

        ponerEnColaThread(&colaThreads, auxInfoThread);
    }

    for (int i = 0; i < nThreads; i++)
    {
        sacarDeColaThread(&colaThreads, &auxInfoThread);
        pthread_join(auxInfoThread->thread_id, (void**)&(auxColaCalc));

        for (int j = 0; j < cargaPThread; j++)
        {
            sacarDeColaCalc(auxColaCalc, &auxInfoCalc);
            // printf("Recibido del thread n# %d el resultado %f\n", i, auxInfoCalc->resultado);
            fprintf(filedst, "%f\n", auxInfoCalc->resultado);
            free(auxInfoCalc);
        }

        free(auxColaCalc);
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
