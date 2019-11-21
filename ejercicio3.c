#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define PATH_LEN 150
#define STR_LEN 300
#define ITEM_ID_LEN 20
#define ARTICULO_LEN 200
#define PRODUCTO_LEN 80
#define MARCA_LEN 80
#define DEFAULT_DATAFILE "articulos.txt"
#define FIFO_IN_FILENAME "/tmp/articulosQueryFifo"
#define FIFO_OUT_FILENAME "/tmp/articulosResultFifo"
#define OPEN_MODE "r"
#define ON_FILE_OPENING_ERROR_MSG "Error en apertura de archivo"
#define MAX_FILTER_LENGTH 220
#define MAX_HEADER_LEN 20
#define MAX_FILTER_VALUE_LEN 200
#define FIFO_PERMISSIONS 0666
#define ON_FORK_ERROR 1
#define TERMINATE_PARENT_PROCESS 0
#define ON_SESSION_ERROR 2
#define ON_OPEN_FILE_ERROR -1
#define STR_OUT_LEN 400
typedef struct
{
    char item_id[ITEM_ID_LEN];
    char articulo[ARTICULO_LEN];
    char producto[PRODUCTO_LEN];
    char marca[MARCA_LEN];
}t_Articulo;

void populateArticulo(t_Articulo*, char*);
void mostrarArticulo(t_Articulo*, int*);
int cumpleFiltro(t_Articulo*, const char*, const char*);
void splitFilter(char*, char*, char*);
int searchInFile();
void handleInputs(char*, char*, char*);
void createDemon(pid_t*, pid_t*, pid_t*);
void createFifos(char*, char*, mode_t);
void logInit();
void mostrarAyuda();
void logMsg(char*);
void removeNewlineAtOffset(char*, int);

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

void mostrarAyuda(){
    printf("Ayuda\n");
}

void createFifos(char* pathFifoIn, char* pathFifoOut, mode_t permissions){
    mkfifo(pathFifoIn, permissions);
    mkfifo(pathFifoOut, permissions);
}

void createDemon(pid_t* p_id, pid_t* c_id, pid_t* s_id){
    *p_id = fork();

    if(*p_id < 0){
        fprintf(stderr, "Error en creacion de proceso... Codigo de error: %d\n", errno);
        exit(ON_FORK_ERROR);
    }
    if(*p_id > 0){
        fprintf(stdout, "Proceso padre finalizado exitosamente!\n");
        exit(TERMINATE_PARENT_PROCESS);
    }

    umask(0);

    *c_id = getpid();
    *s_id = setsid();
    
    if(*s_id < 0){
        fprintf(stderr, "Error en creacion de sesion... Codigo de error: %d\n", errno);
        exit(ON_SESSION_ERROR);
    }

    fprintf(stdout, "Proceso hijo creado exitosamente. PID: %d\n", getpid());

    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void logInit(){
	FILE* fAux = fopen("/tmp/initLog", "w");
	char initLogMsg[] = "Successful init of Daemon...\n";
        fwrite(initLogMsg, sizeof(initLogMsg), 1, fAux);
	fclose(fAux);
}

void logMsg(char* msg){
	FILE* fpLog = fopen("/tmp/log", "a");
	fwrite(msg, strlen(msg), 1, fpLog);
	fclose(fpLog);
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
        populateArticulo(&articulo, line);
        if(cumpleFiltro(&articulo, filterItem, filterValue)){
 		    mostrarArticulo(&articulo, fdWrite);
	    }
    }
    fclose(fp);
    return 0;
}

void removeNewlineAtOffset(char* string, int offset){
    char* newLine = strrchr(string, '\n') + offset;
    if(newLine != NULL){
        *newLine = '\0';
    }
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

int cumpleFiltro(t_Articulo* pArticulo, const char* filterItem, const char* filterValue){
    return  (!strcmp(filterItem, "ITEM_ID") && !strcmp(filterValue, pArticulo->item_id)) ||
            (!strcmp(filterItem, "ARTICULO") && !strcmp(filterValue, pArticulo->articulo)) ||
            (!strcmp(filterItem, "PRODUCTO") && !strcmp(filterValue, pArticulo->producto)) ||
            (!strcmp(filterItem, "MARCA") && !strcmp(filterValue, pArticulo->marca));
}
