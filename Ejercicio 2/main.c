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

int main(int argc, char *argv[]) {
    char line[LINE_LEN], *aux;
    FILE *filesrc;
    FILE *filedst;
    char* fileIn;
    char* fileOut;
    double resultado;
    t_par par;
    int threads = 0;
    int nLineas = 0;
    int nThreads = 0;

    validateParams(argc, argv, &threads, fileIn, fileOut);
    
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
        fprintf(stderr, "Error: linea numero %d con formato incorrecto: %s.\n", nLineas, line);
        exit(INVALID_DATA);
    }

    // while(fgets(line, sizeof(line), filesrc)) {
    //     resultado=0;
        
    //     trozarCampos(&par, line);
    //     resultado = par.primero + par.segundo;
    //     fprintf(filedst, "%lf\n", resultado);
    // }

    fclose(filesrc);
    fclose(filedst);
    // printf("Cantidad de threads: %d\n", threads);
    return 0;
}

// int contarLineasEnArchivo(FILE* fp){
//     rewind(fp);
//     int nLineas = 0;
//     char charActual = EOF;

//     while((charActual=fgetc(fp))!=EOF) {
//       if(charActual=='\n')
//          nLineas++;
//     }

//    return nLineas;
// }

