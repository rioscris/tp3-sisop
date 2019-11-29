#ifndef COLADINAMICA_H_INCLUDED
#define COLADINAMICA_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct{
    pthread_t thread_id;
}tInfoThread;

typedef struct{
    double primero;
    double segundo;
    double resultado;
}tInfoCalc;

typedef struct sNodoCalc{
    tInfoCalc* info;
    struct sNodoCalc* sig;
}tNodoCalc;

typedef struct sNodoThread{
    tInfoThread* info;
    struct sNodoThread* sig;
}tNodoThread;

typedef struct{
    tNodoCalc   *pri,
                *ult;
}tColaCalc;

typedef struct{
    tNodoThread *pri,
                *ult;
}tColaThread;

void crearColaCalc(tColaCalc *p);
int colaLlenaCalc(const tColaCalc *p);
int ponerEnColaCalc(tColaCalc *p, tInfoCalc *d);
int colaVaciaCalc(const tColaCalc *p);
int sacarDeColaCalc(tColaCalc *p, tInfoCalc **d);

void crearColaThread(tColaThread *p);
int colaLlenaThread(const tColaThread *p);
int ponerEnColaThread(tColaThread *p, tInfoThread *d);
int colaVaciaThread(const tColaThread *p);
int sacarDeColaThread(tColaThread *p, tInfoThread **d);

#endif // COLADINAMICA_H_INCLUDED
