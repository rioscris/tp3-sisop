#include "main.h"

#define PATH_LEN 150
#define DEFAULT_DATAFILE "articulos.txt"
#define FIFO_IN_FILENAME "/tmp/articulosQueryFifo"
#define FIFO_OUT_FILENAME "/tmp/articulosResultFifo"
#define ON_FILE_OPENING_ERROR_MSG "Error en apertura de archivo"
#define FIFO_PERMISSIONS 0666

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

