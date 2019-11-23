#include "main.h"

#define PATH_LEN 150
#define DEFAULT_DATAFILE "articulos.txt"
#define FIFO_IN_FILENAME "/tmp/articulosQueryFifo"
#define FIFO_OUT_FILENAME "/tmp/articulosResultFifo"
#define ON_FILE_OPENING_ERROR_MSG "Error en apertura de archivo"
#define FIFO_PERMISSIONS 0666
#define PARAMETER_ERROR -3

int main(int argc, char** argv){
    pid_t p_id;
    pid_t c_id;
    pid_t s_id;
    
    char option;
    char pathToFile[PATH_LEN] = "/0";
    while ((option = getopt (argc, argv, "p:h")) != -1)
        switch (option)
        {
            case 'h':
                mostrarAyuda();
                return 0;
            case 'p':
                if(argc == 3){
                    strcpy(pathToFile, optarg);
                }
                else{
                    fprintf(stdout, "Los parametros recibidos son incorrectos.\n");
                    fprintf(stdout, "Para recibir ayuda, ingrese el parametro -h\n");
                    exit(PARAMETER_ERROR);
                }
                break;
            default:
                fprintf(stdout, "Los parametros recibidos son incorrectos.\n");
                exit(PARAMETER_ERROR);
        }
    if(argc == 1){
        fprintf(stdout, "Para correr el demonio se necesita especificar el archivo de base de datos con el parametro -p <path>\n");
        fprintf(stdout, "Para recibir ayuda, ingrese el parametro -h\n");
        exit(PARAMETER_ERROR);
    }
    fprintf(stderr, "Iniciando creacion de demonio para consultas...\n");
    createDemon(&p_id, &c_id, &s_id);
    createFifos(FIFO_IN_FILENAME, FIFO_OUT_FILENAME, FIFO_PERMISSIONS);
    handleInputs(FIFO_IN_FILENAME, FIFO_OUT_FILENAME, pathToFile);
    return 0;
}

