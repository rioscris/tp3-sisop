#include "colaDinamica.h"

//Calc
void crearColaCalc(tColaCalc *p)
{
    p->pri = NULL;
    p->ult = NULL;
}
int colaLlenaCalc(const tColaCalc *p)
{
    tNodoCalc *aux = (tNodoCalc*)malloc(sizeof(tNodoCalc));
    free(aux);
    return aux == NULL;
}
int ponerEnColaCalc(tColaCalc *p, tInfoCalc *d)
{
    tNodoCalc *nue = (tNodoCalc*)malloc(sizeof(tNodoCalc));
    if( nue == NULL)
          return 0;
    nue->info = d;
    if( p->pri == NULL )
        p->pri = nue;
    else
        p->ult->sig = nue;

    p->ult = nue;

    nue->sig = NULL;
    return 1;
}
int colaVaciaCalc(const tColaCalc *p)
{
    return p->pri == NULL;
}
int sacarDeColaCalc(tColaCalc *p, tInfoCalc **d)
{
    tNodoCalc *aux;

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

//Thread
void crearColaThread(tColaThread *p)
{
    p->pri = NULL;
    p->ult = NULL;
}
int colaLlenaThread(const tColaThread *p)
{
    tNodoThread *aux = (tNodoThread*)malloc(sizeof(tNodoThread));
    free(aux);
    return aux == NULL;
}
int ponerEnColaThread(tColaThread *p, tInfoThread *d)
{
    tNodoThread *nue = (tNodoThread*)malloc(sizeof(tNodoThread));
    if( nue == NULL)
          return 0;
    nue->info = d;
    if( p->pri == NULL )
        p->pri = nue;
    else
        p->ult->sig = nue;

    p->ult = nue;

    nue->sig = NULL;
    return 1;
}
int colaVaciaThread(const tColaThread *p)
{
    return p->pri == NULL;
}
int sacarDeColaThread(tColaThread *p, tInfoThread **d)
{
    tNodoThread *aux;

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
