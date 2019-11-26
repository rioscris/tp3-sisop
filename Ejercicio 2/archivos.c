#include "archivos.h"

int contarLineasEnArchivo(FILE* fp, int* nLineas) {
    rewind(fp);
    *nLineas = 0;
    char line[LINE_LEN];

    while(fgets(line, sizeof(line), fp)) {
        (*nLineas)++;
        if(!isValidPair(line))
            return INVALID_DATA;
    }
    
    return *nLineas;
}

int isValidPair(char* line) {
    return (strchr(line, '\0') && strlen(line) > 1 && strchr(line, ','));
}

int abrirArchivo(FILE **fp,const char *nombre,const char *modo) {
    *fp = fopen(nombre,modo);
    return *fp!=NULL;
}

void trozarCampos(t_par *d,char *s) {
    char *aux = strchr(s,'\n');
    *aux = '\0';
    aux = strrchr(s,',');
    sscanf(aux+1,"%lf",&d->primero);
    *aux='\0';
    sscanf(s,"%lf",&d->segundo);
}