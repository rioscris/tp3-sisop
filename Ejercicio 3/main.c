#include "main.h"

int main(int argc, char** argv){
    pid_t p_id;
    pid_t c_id;
    pid_t s_id;

    char pathToFile[PATH_LEN];
    char fifoIn[PATH_LEN];
    char fifoOut[PATH_LEN];
    char logger[PATH_LEN] = "\0";

    validParams(argc, argv, pathToFile, fifoIn, fifoOut, logger, DEFAULT_LOGGER);
    initLog(logger, DEFAULT_LOGGER);

    fprintf(stdout, "Iniciando creacion de demonio para consultas...\n");
    createDemon(&p_id, &c_id, &s_id);
    createFifos(fifoIn, fifoOut, FIFO_PERMISSIONS, logger);
    handleInputs(fifoIn, fifoOut, pathToFile, logger);
    return 0;
}
