#include "ejercicio3.h"

#define PATH_LEN 150
#define STR_LEN 300
#define DEFAULT_DATAFILE "articulos.txt"
#define FIFO_IN_FILENAME "/tmp/articulosQueryFifo"
#define FIFO_OUT_FILENAME "/tmp/articulosResultFifo"
#define OPEN_MODE "r"
#define ON_FILE_OPENING_ERROR_MSG "Error en apertura de archivo"
#define MAX_FILTER_LENGTH 220
#define MAX_HEADER_LEN 20
#define MAX_FILTER_VALUE_LEN 200
#define FIFO_PERMISSIONS 0666
#define ON_OPEN_FILE_ERROR -1
#define STR_OUT_LEN 400

void populateArticulo(t_Articulo*, char*);
void mostrarArticulo(t_Articulo*, int*);
int cumpleFiltro(t_Articulo*, t_Articulo*, const char*, const char*);
void splitFilter(char*, char*, char*);
int searchInFile();
void handleInputs(char*, char*, char*);

int main(int argc, char** argv){
    pid_t p_id;
    pid_t c_id;
    pid_t s_id;
    
    char option;
    char pathToFile[PATH_LEN] = "./articulos";
    while ((option = getopt (argc, argv, "p:h")) != -1)
        switch (option)
        {
            case 'h':
                mostrarAyuda();
                return 0;
            case 'p':            
                strcpy(pathToFile, optarg);
                break;
	    default:
		fprintf(stdout, "Se necesita especificar un parametro -h o -p <path>...\n");
		abort();		
        }
    fprintf(stdout, "Iniciando demonio para el archivo '%s'...\n", pathToFile);
    createDemon(&p_id, &c_id, &s_id);
    createFifos(FIFO_IN_FILENAME, FIFO_OUT_FILENAME, FIFO_PERMISSIONS);
    handleInputs(FIFO_IN_FILENAME, FIFO_OUT_FILENAME, pathToFile);
    return 0;
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



void populateArticulo(t_Articulo* pArticulo, char* line){
    char *pChar = NULL;
    removeNewlineAtOffset(line, -1);

    pChar = strrchr(line, ';');
    strcpy(pArticulo->marca, pChar+1);
    *pChar = '\0';

    pChar = strrchr(line, ';');
    strcpy(pArticulo->producto, pChar+1);
    *pChar = '\0';

    pChar = strrchr(line, ';');
    strcpy(pArticulo->articulo, pChar+1);
    *pChar = '\0';

    strcpy(pArticulo->item_id, line);
    *line = '\0';
}

void mostrarArticulo(t_Articulo* pArticulo, int* fdWrite){
    char result[STR_OUT_LEN];
    sprintf(result, "%s\t%s\t%s\t%s\n", pArticulo->item_id, pArticulo->articulo, pArticulo->producto, pArticulo->marca);
    write(*fdWrite, result, strlen(result));
}

void splitFilter(char* filter, char* filterItem, char* value){
    char* pChar = NULL;

    removeNewlineAtOffset(filter, 0);

    pChar = strrchr(filter, '=');
    strcpy(value, pChar+1);
    *pChar = '\0';

    strcpy(filterItem, filter);
}

int cumpleFiltro(t_Articulo* pArticulo, t_Articulo* encabezados, const char* filterItem, const char* filterValue){
    return  (!strcmp(filterItem, encabezados->item_id) && !strcmp(filterValue, pArticulo->item_id)) ||
            (!strcmp(filterItem, encabezados->articulo) && !strcmp(filterValue, pArticulo->articulo)) ||
            (!strcmp(filterItem, encabezados->producto) && !strcmp(filterValue, pArticulo->producto)) ||
            (!strcmp(filterItem, encabezados->marca) && !strcmp(filterValue, pArticulo->marca));
}
