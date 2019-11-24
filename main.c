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

    char pathToFile[PATH_LEN] = "/0";
    
    validParams(argc, argv, pathToFile);
    
    fprintf(stdout, "Iniciando creacion de demonio para consultas...\n");
    createDemon(&p_id, &c_id, &s_id);
    createFifos(FIFO_IN_FILENAME, FIFO_OUT_FILENAME, FIFO_PERMISSIONS);
    handleInputs(FIFO_IN_FILENAME, FIFO_OUT_FILENAME, pathToFile);
    return 0;
}
