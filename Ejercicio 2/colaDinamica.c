
#include "colaDinamica.h"

void crearCola(tCola *p)
{
    p->pri = NULL;
    p->ult = NULL;
}
int colaLlena(const tCola *p)
{
    tNodo *aux = (tNodo*)malloc(sizeof(tNodo));
    free(aux);
    return aux == NULL;
}
int ponerEnCola(tCola *p, const tInfo *d)
{
    tNodo *nue = (tNodo*)malloc(sizeof(tNodo));
    if( nue == NULL)
          return 0;
    nue->info = *d;
    if( p->pri == NULL )
        p->pri = nue;
    else
        p->ult->sig = nue;

    p->ult = nue;

    nue->sig = NULL;
    return 1;
}
int colaVacia(const tCola *p)
{
    return p->pri == NULL;
}
int sacarDeCola(tCola *p, tInfo *d)
{
    tNodo *aux;

    if( p->pri == NULL )
        return 0;///cola_vacia

    aux = p->pri;
    *d = aux->info;
    if( p->pri == p->ult )
    {
        p->ult = NULL;
        p->pri= NULL;
    }
    else
        p->pri = aux->sig;

    free(aux);
    return 1;
}
