#include "filtro.h"

void splitFilter(char* filter, char* filterItem, char* value){
    char* pChar = NULL;

    removeNewlineAtOffset(filter, 0);

    pChar = strrchr(filter, '=');
    strcpy(value, pChar+1);
    *pChar = '\0';

    strcpy(filterItem, filter);
}

int cumpleFiltro(t_Articulo* pArticulo, t_Articulo* encabezados, const char* filterItem, const char* filterValue){
    return  (!strcmp(filterItem, encabezados->item_id) && !strcmp(filterValue, pArticulo->item_id)) ||
            (!strcmp(filterItem, encabezados->articulo) && !strcmp(filterValue, pArticulo->articulo)) ||
            (!strcmp(filterItem, encabezados->producto) && !strcmp(filterValue, pArticulo->producto)) ||
            (!strcmp(filterItem, encabezados->marca) && !strcmp(filterValue, pArticulo->marca));
}