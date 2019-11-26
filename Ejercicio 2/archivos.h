#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "definiciones.h"

int contarLineasEnArchivo(FILE* fp, int* nLineas);
int isValidPair(char* line);
int abrirArchivo(FILE **fp,const char *nombre,const char *modo);
void trozarCampos(t_par *d,char *s);