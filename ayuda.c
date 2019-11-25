#include "ayuda.h"

void mostrarAyuda(const char* defaultLogger){
    printf("Grupo 6 - TP3 - Segunda entrega\n");
    printf("Rios Cristian (40.015.557)\n");
    printf("Christian Riveros (27.932.808)\n");
    printf("Diego Nuñez (36.159.969)\n");
    printf("Luis Villca (35.277.730)\n\n");

    printf("El presente script crea un demonio que lee consultas sobre un archivo de datos, de un fifo de entrada recibido por parametro con la opcion (-i).\n");
    printf("Posteriormente, retorna el resultado en un fifo de salida recibido por parametro con la opcion (-o).\n\n");
    printf("Para esto se le debe pasar al programa por parametro (-p) la ruta del archivo de datos a leer.\n");
    printf("Opcionalmente, se puede pasar por parametro (-l) la ubicacion de un archivo para loggear ciertos estados del demonio.\n");
    printf("Por defecto, de no pasarse ningun parametro, el proceso intentara crear el logger en la ubicacion relativa <%s>.\n\n", defaultLogger);

    printf("Uso del programa:\n");
    printf("\tejercicio3 -p <path> -i <fifo de entrada> -o <fifo de salida> [-l <logger>]\n\n");
    
    printf("Las consultas deben tener el formato:\n");
    printf("\tITEM_ID=[numero]\n");
    printf("\tPRODUCTO=[nombre de producto]\n");
    printf("\tITEM_ID=111\n");
    printf("\tMARCA=MAROLIO\n\n");

    printf("Consideraciones importantes\n");
    printf("* Las consultas llegan de a una por vez.\n");
    printf("* Los fifos pasados por parametros no deben existir previamente, solo los crea si no existen previamente. ");
    printf("Dado el caso, el proceso termina sin eliminarlos (revisar el logger) para no interferir con otros procesos que puedan estar requiriendolos en el momento.\n");
    printf("* El proceso puede llegar a detenerse sin registrar informacion en el logger en caso de que haya errores de escritura con el mismo. \n");
    printf("Por ejemplo, que no se tenga permiso de escritura al mismo.\n");
    printf("* De forma analoga al item anterior, la creacion de los fifos podria fallar y detener el programa, si la ubicacion de los mismos ");
    printf("implica un error considerable (revisar el logger) para la funcion 'mkfifo', por ejemplo, segun la ubicacion. \n");
    printf(" - En cualquiera de los ultimos dos casos, probar cambiar la ubicacion de los archivos (por ejemplo a /tmp/) -\n\n");

    printf("Ejemplo de uso:\n");
    printf("$\tejercicio3 -p ./articulos.txt -i /tmp/fifoIn -o /tmp/fifoOut ./log\n");
    printf("Lectura de resultados:\n");
    printf("$\tcat /tmp/fifoOut\n");
    printf("Envio de consultas:\n");
    printf("$\techo 'PRODUCTO=PIZZA' > /tmp/fifoIn\n\n");
}