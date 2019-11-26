/*
Trabajo Practico Grupal Numero 3 - Ejercicio 2
Nombre del Script: Manejo de archivos comprimidos
Primera entrega

Integrantes:
Nuñez Diego - DNI 36.159.969
Rios Cristian - DNI 40.015.557
Riveros Christian - DNI 37.932.808
Villca Luis - DNI 35.277.730
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
//#include <pthread.h>

#define CON_MSJ 1

typedef struct
{
    double primero;
    double segundo;
}t_par;

int abrirArchivo(FILE **fp,const char *nombre,const char *modo,int conSin);
void trozarCampos(t_par *d,char *s);
void ayuda();

int main(int argc, char *argv[])
{
    char numero[20], *aux;
    FILE *filesrc;
    FILE *filedst;
    double resultado;
    t_par par;
    int threads = atoi(argv[3]);

    if(argv[1] == NULL)
        ayuda();
        
    if(!abrirArchivo(&filesrc,argv[1],"r",CON_MSJ))
        exit(1);

    if(!abrirArchivo(&filedst,argv[2],"w",CON_MSJ))
        exit(1);

    while(fgets(numero,sizeof(numero),filesrc))
    {
        resultado=0;
        aux = strchr(numero,'\n');
        if(aux==NULL)
        {
            fclose(filesrc);
            fclose(filedst);
            fprintf(stderr,"Error: archivo demasiado largo\n");
            exit (2);
        }
        trozarCampos(&par,numero);
        resultado=par.primero+par.segundo;
        fprintf(filedst,"%lf\n",resultado);
    }
    fclose(filesrc);
    fclose(filedst);
    printf("Cantidad de threads: %d\n", threads);
    return 0;
}

int abrirArchivo(FILE **fp,const char *nombre,const char *modo,int conSin)
{
    *fp = fopen(nombre,modo);
    if(*fp==NULL)
    {
        if(conSin==CON_MSJ)
            printf("Error abriendo \"%s\" en modo \"%s\".\n",nombre,modo);
        return 0;
    }
    return 1;
}

void trozarCampos(t_par *d,char *s)
{
    char *aux = strchr(s,'\n');
    *aux = '\0';
    aux = strrchr(s,',');
    sscanf(aux+1,"%lf",&d->primero);
    *aux='\0';
    sscanf(s,"%lf",&d->segundo);
}

void ayuda()
{
    printf("\nAyuda:\n");
    printf("    El script lee los pares pertenecientes a dos vectores desde un archivo y los suma dejando el vector resultante en otro archivo\n");
    printf("    Ejecutar con los siguientes parametros:\n");
    printf("        Primer parametro: Ruta del archivo a leer entre comillas\n");
    printf("        Segundo parametro: Ruta del archivo a escribir entre comillas\n");
    printf("        Tercer parametro: Cantidad de Threads\n");
}
