#include "fifos.h"

void createFifos(char* pathFifoIn, char* pathFifoOut, mode_t permissions){
    mkfifo(pathFifoIn, permissions);
    mkfifo(pathFifoOut, permissions);
}