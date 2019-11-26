#include "articulosFunc.h"

void populateArticulo(t_Articulo* pArticulo, char* line){
    char *pChar = NULL;
    removeNewlineAtOffset(line, -1);

    pChar = strrchr(line, ';');
    strcpy(pArticulo->marca, pChar+1);
    *pChar = '\0';

    pChar = strrchr(line, ';');
    strcpy(pArticulo->producto, pChar+1);
    *pChar = '\0';

    pChar = strrchr(line, ';');
    strcpy(pArticulo->articulo, pChar+1);
    *pChar = '\0';

    strcpy(pArticulo->item_id, line);
    *line = '\0';
}

void mostrarArticulo(t_Articulo* pArticulo, int* fdWrite){
    char result[STR_OUT_LEN];
    sprintf(result, "%s\t%s\t%s\t%s\n", pArticulo->item_id, pArticulo->articulo, pArticulo->producto, pArticulo->marca);
    write(*fdWrite, result, strlen(result));
}
