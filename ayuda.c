#include "ayuda.h"

void mostrarAyuda(){
    printf("Grupo 6 - TP3 - Primera entrega\n");
    printf("Rios Cristian (40.015.557)\n");
    printf("Christian Riveros (27.932.808)\n");
    printf("Diego Nuñez (36.159.969)\n");
    printf("Luis Villca (35.277.730)\n");
    printf("El presente script crea un demonio que lee consultas de un fifo de entrada ubicado en /tmp/articulosQueryFifo\n");
    printf("y los retorna en un fifo de salida ubicado en /tmp/articulosResultFifo\n\n");
    printf("Para esto se le debe pasar al programa por parametro (-p) la ruta del archivo de datos a leer, de la siguiente forma\n");
    printf("ejercicio3 -p <path>\n\n");
    printf("Las consultas deben tener el formato:\n");
    printf("ITEM_ID=[numero]:\n");
    printf("PRODUCTO=[nombre de producto]:\n");
    printf("ITEM_ID=111:\n");
    printf("MARCA=MAROLIO:\n\n");
    printf("Consideracion: Las consultas llegan de a una por vez\n");
}