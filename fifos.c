#include "fifos.h"

void createFifos(char* pathFifoIn, char* pathFifoOut, mode_t permissions){
    mkfifo(pathFifoIn, permissions);
    mkfifo(pathFifoOut, permissions);
}

void handleInputs(char* pathFifoIn, char* pathFifoOut, char* pathToData){
    char filtro[MAX_FILTER_LENGTH];
    logInit();
    int queryFD = open(pathFifoIn, O_RDWR);
    int resultFD = open(pathFifoOut, O_WRONLY);

    while(read(queryFD, filtro, MAX_FILTER_LENGTH)>0){
	if(searchInFile(filtro, &resultFD, pathToData) != 0)
            break;
    }

    close(queryFD);
    close(resultFD);
}

int searchInFile(char* filtro, int* fdWrite, char* pathToData){
    FILE *fp = NULL;
    char line[STR_LEN];
    t_Articulo articulo;
    t_Articulo encabezados;
    int esEncabezado = 1;
    // Dividir filtro en dos cadenas, antes y despues del '='
    char filterItem[MAX_HEADER_LEN];
    char filterValue[MAX_FILTER_VALUE_LEN];
    splitFilter(filtro, filterItem, filterValue);
	
    // Apertura del archivo de articulos
    fp = fopen(pathToData, OPEN_MODE);
    if(!fp)
        return ON_OPEN_FILE_ERROR;
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