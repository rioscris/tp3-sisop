#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#include "ayuda.h"
#define PARAMETER_ERROR -3
#define ON_HELP_DISPLAY -4
#define HELP_MSG "Para recibir ayuda, ingrese el parametro -h\n"
#define toggle(X) X=!X
void validParams(int, char**, char*, char*, char*, char*, const char*);