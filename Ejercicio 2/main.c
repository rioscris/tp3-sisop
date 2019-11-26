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

FILE* filesrc;
FILE* filedst;

void *threadCalc(void* paramPar){
    t_infoTh* auxPar = (t_infoTh*) paramPar;
    char line[LINE_LEN];
    t_par par;
    int cargaPThread = auxPar->cargaPThread;
    
    int iCargaThread;
    double resultado = 0;
    for(iCargaThread = 0; iCargaThread < cargaPThread; iCargaThread++){
        if(!fgets(line, sizeof(line), filesrc)){
            break;
        }
        trozarCampos(&par, line);
        resultado = par.primero + par.segundo;
        printf("Resultado %lf\n", resultado);
        fprintf(filedst, "%lf\n", resultado);
    }
    free(paramPar);
}

int main(int argc, char *argv[]) {
    char line[LINE_LEN], *aux;
    char fileIn[PATH_LEN];
    char fileOut[PATH_LEN];
    double resultado;
    t_infoTh* infoThread;
    t_par* auxPar;
    pthread_t thread_id;
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

    // Carga de trabajo a los threads
    rewind(filesrc);
    rewind(filedst);


    for(iThread = 0; iThread < nThreads; iThread++){
        infoThread = (t_infoTh *) malloc(sizeof(t_infoTh));
        if(!infoThread){
            fprintf(stderr, "Error en pedido de memoria dinamica.\n");
            break;
        }

        // infoThread->filesrc = filesrc;
        // infoThread->filedst = filedst;

        infoThread->cargaPThread = cargaPThread;
        
        pthread_create(&thread_id, NULL, threadCalc, infoThread);
        
    }

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
