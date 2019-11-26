#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define PARAMETER_ERROR -3
#define ON_HELP_DISPLAY -4
#define HELP_MSG "Para recibir ayuda, ingrese el parametro -h\n"
#define toggle(X) X=!X

void validateParams(int argc, char** argv, int* threads, char* fileIn, char* fileOut);
void ayuda();