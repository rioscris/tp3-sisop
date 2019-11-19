#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define STR_LEN 300
#define ARTICULO_LEN 200
#define PRODUCTO_LEN 80
#define MARCA_LEN 80
#define FILENAME "articulos.txt"
#define OPEN_MODE "r"
#define ON_FILE_OPENING_ERROR_MSG "Error en apertura de archivo"
#define MAX_HEADER_LEN 20
#define MAX_FILTER_VALUE_LEN 200
#define FIFO_PERMISSIONS 0666
#define ON_FORK_ERROR 1
#define TERMINATE_PARENT_PROCESS 0
#define ON_SESSION_ERROR 2
typedef struct
{
    int item_id;
    char articulo[ARTICULO_LEN];
    char producto[PRODUCTO_LEN];
    char marca[MARCA_LEN];
}t_Articulo;

void populateArticulo(t_Articulo*, char*);
void mostrarArticulo(t_Articulo*);
void mostrarEncabezados();
int cumpleFiltro(t_Articulo*, char*, char*);
void splitFilter(char*, char*, char*);
int fileHandler();
void handleInputs();
void createDemon(pid_t*, pid_t*, pid_t*);
void createFifo(char*);

int main(){
    pid_t p_id;
    pid_t c_id;
    pid_t s_id;
    
    createDemon(&p_id, &c_id, &s_id);
    createFifo(FILENAME);
    handleInputs();
    return 0;
}

void createFifo(char* filename){
    mkfifo(filename, FIFO_PERMISSIONS);
}

void createDemon(pid_t* p_id, pid_t* c_id, pid_t* s_id){
    *p_id = fork();

    if(*p_id < 0){
        fprintf(stderr, "Error en creacion de proceso... Codigo de error: %d\n", errno);
        exit(ON_FORK_ERROR);
    }
    if(*p_id > 0){
        exit(TERMINATE_PARENT_PROCESS);
    }

    umask(0);

    *c_id = getpid();
    *s_id = setsid();
    
    if(*s_id < 0){
        fprintf(stderr, "Error en creacion de sesion... Codigo de error: %d\n", errno);
        exit(ON_SESSION_ERROR);
    }

    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}

void handleInputs(){
    
}

int fileHandler(){
    FILE *fp = NULL;
    char line[STR_LEN];
    t_Articulo articulo;
    int nLinea = 0;
    char filtro[] = "PRODUCTO=SET HERMETICOS";
    fp = fopen(FILENAME, OPEN_MODE);

    char filterItem[MAX_HEADER_LEN];
    char filterValue[MAX_FILTER_VALUE_LEN];
    splitFilter(filtro, filterItem, filterValue);
    if(!fp){
        fprintf(stderr, "%s\n", ON_FILE_OPENING_ERROR_MSG);
        return -1;
    }
    rewind(fp);


    while(fgets(line, STR_LEN, fp)){
        nLinea++;
        if(nLinea == 1){
            mostrarEncabezados();
            continue;
        }
        populateArticulo(&articulo, line);
        if(cumpleFiltro(&articulo, filterItem, filterValue))
            mostrarArticulo(&articulo);
    }
    fclose(fp);
    return 0;
}

void populateArticulo(t_Articulo* pArticulo, char* line){
    char *pChar = NULL;

    pChar = strrchr(line, ';');
    strcpy(pArticulo->marca, pChar+1);
    *pChar = '\0';

    pChar = strrchr(line, ';');
    strcpy(pArticulo->producto, pChar+1);
    *pChar = '\0';

    pChar = strrchr(line, ';');
    strcpy(pArticulo->articulo, pChar+1);
    *pChar = '\0';

    sscanf(line, "%d", &pArticulo->item_id);
}

void mostrarArticulo(t_Articulo* pArticulo){
    fprintf(stdout, "%d\t%s\t%s\t%s", pArticulo->item_id, pArticulo->articulo, pArticulo->producto, pArticulo->marca);
}

void mostrarEncabezados(){
    fprintf(stdout, "ITEM_ID\tARTICULO\tPRODUCTO\tMARCA\n");
}

void splitFilter(char* filter, char* filterItem, char* value){
    char* pChar = NULL;

    pChar = strrchr(filter, '=');
    strcpy(value, pChar+1);
    *pChar = '\0';

    strcpy(filterItem, filter);
}

int cumpleFiltro(t_Articulo* pArticulo, char* filterItem, char* filterValue){
    return  (!strcmp(filterItem, "ITEM_ID") && atoi(filterValue) == pArticulo->item_id) ||
            (!strcmp(filterItem, "ARTICULO") && !strcmp(filterValue, pArticulo->articulo)) ||
            (!strcmp(filterItem, "PRODUCTO") && !strcmp(filterValue, pArticulo->producto)) ||
            (!strcmp(filterItem, "MARCA") && !strcmp(filterValue, pArticulo->marca));
}