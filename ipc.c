#include "ipc.h"

void createFifos(char* pathFifoIn, char* pathFifoOut, mode_t permissions, char* logger){
    char logBuffer[LOG_LEN];
    if(mkfifo(pathFifoIn, permissions) == -1){
        sprintf(logBuffer, "-Error en creacion de fifo de entrada:\n%s\n", strerror(errno));
        logMessage(logBuffer, logger);
        exit(FIFO_ERROR);
    }
    if(mkfifo(pathFifoOut, permissions) == -1){
        sprintf(logBuffer, "-Error en creacion de fifo de salida:\n%s\n", strerror(errno));
        logMessage(logBuffer, logger);
        exit(FIFO_ERROR);
    }
}

void handleInputs(char* pathFifoIn, char* pathFifoOut, char* pathToData, char* logger){
    char filtro[MAX_FILTER_LENGTH];
    int queryFD = open(pathFifoIn, O_RDWR);
    char logBuffer[LOG_LEN];
    if(queryFD == -1){
        sprintf(logBuffer, "-Error en apertura de fifo de entrada: %s\n", strerror(errno));
        logMessage(logBuffer, logger);
        exit(FIFO_ERROR);
    }
    
    int resultFD = open(pathFifoOut, O_WRONLY);
    if(resultFD == -1){
        sprintf(logBuffer, "-Error en apertura de fifo de salida: %s\n", strerror(errno));
        logMessage(logBuffer, logger);
        exit(FIFO_ERROR);
    }
        
    while(read(queryFD, filtro, MAX_FILTER_LENGTH)>0){
        sprintf(logBuffer, "-Recibida Consulta:\n%s\n", filtro);
        logMessage(logBuffer, logger);

        if(searchInFile(filtro, &resultFD, pathToData, logger) != 0)
            break;
    }

    sprintf(logBuffer, "-Terminando servidor...\n");
    logMessage(logBuffer, logger);
    
    close(queryFD);
    close(resultFD);
}

int searchInFile(char* filtro, int* fdWrite, char* pathToData, char* logger){
    FILE *fp = NULL;
    char line[STR_LEN];
    t_Articulo articulo;
    t_Articulo encabezados;
    int esEncabezado = 1;
    char logBuffer[LOG_LEN];
    // Dividir filtro en dos cadenas, antes y despues del '='
    char filterItem[MAX_HEADER_LEN];
    char filterValue[MAX_FILTER_VALUE_LEN];
    splitFilter(filtro, filterItem, filterValue);
	
    // Apertura del archivo de articulos
    fp = fopen(pathToData, OPEN_MODE);
    if(!fp){
        sprintf(logBuffer, "-Error en apertura de archivo de datos: %s\n", strerror(errno));
        logMessage(logBuffer, logger);
        return ON_OPEN_FILE_ERROR;
    }
    rewind(fp);

    while(fgets(line, STR_LEN, fp)){
        if(esEncabezado){
            populateArticulo(&encabezados, line);
            esEncabezado = !esEncabezado;
        }
        else{
            populateArticulo(&articulo, line);
            if(cumpleFiltro(&articulo, &encabezados, filterItem, filterValue)){
                mostrarArticulo(&articulo, fdWrite);
            }
        }
    }
    fclose(fp);
    return 0;
}