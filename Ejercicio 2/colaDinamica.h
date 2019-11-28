#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct
{
    pthread_t thread_id;
}tInfo;

typedef struct sNodo
{
    tInfo info;
    struct sNodo* sig;
}tNodo;

typedef struct
{
    tNodo *pri,
          *ult;
}tCola;


void crearCola(tCola *p);
int colaLlena(const tCola *p);
int ponerEnCola(tCola *p, const tInfo *d);
int colaVacia(const tCola *p);
int sacarDeCola(tCola *p, tInfo *d);

#endif // COLADINAMICA_H_INCLUDED
