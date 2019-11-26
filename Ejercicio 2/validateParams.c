#include "validateParams.h"

void validateParams(int argc, char** argv, int* threads, char* fileIn, char* fileOut){
    int index; 
    char option;
    int tFlag = 0;
    int iFlag = 0;
    int oFlag = 0;
    if (argc == 1) {
        fprintf(stdout, "Para correr el programa se debe especificar el archivo de entrada con -i, el archivo de salida con -o, y el numero de threads con -t.\n");
        fprintf(stderr, HELP_MSG);
        exit(PARAMETER_ERROR);
    }
    while ((option = getopt (argc, argv, ":i:o:t:h")) != -1)
        switch (option)
        {
            case 'h':
                ayuda();
                exit(ON_HELP_DISPLAY);
                break;
            case 'i':
                toggle(iFlag);
                strcpy(fileOut, optarg);
                break;
            case 'o':
                toggle(oFlag);
                strcpy(fileIn, optarg);
                break;
            case 't':
                toggle(tFlag);
                *threads = atoi(optarg);
                break;
            case ':':
                if(optopt == 't'){
                    fprintf(stderr, "No se ha recibido ningun parametro <int> para la opcion -t.\n");
		            fprintf(stderr, "Por favor, especifique el numero de threads necesarios.\n");
		        }
                else if(optopt == 'i'){
                    fprintf(stderr, "No se ha recibido ningun parametro <path> para la opcion -i.\n");
		            fprintf(stderr, "Por favor, especifique la ubicacion del archivo con los vectores.\n");
		        }
                else if(optopt == 'o'){
                    fprintf(stderr, "No se ha recibido ningun parametro <path> para la opcion -o.\n");
		            fprintf(stderr, "Por favor, especifique la ubicacion del archivo de resultado.\n");
		        }
                else{
		            fprintf(stderr, "Los parametros recibidos son incorrectos.\n");
                }
                fprintf(stderr, HELP_MSG);
                exit(PARAMETER_ERROR);
            case '?':
                fprintf(stderr, "No se reconoce la opcion %c\n", optopt);
                fprintf(stderr, HELP_MSG);
                exit(PARAMETER_ERROR);
            default:
                exit(PARAMETER_ERROR);
        }
    for (index = optind; index < argc; index++){
        fprintf(stdout, "ERROR: Se ha recibido un parametro no reconocido: %s\n", argv[index]);
        fprintf(stderr, HELP_MSG);
        exit(PARAMETER_ERROR);
    }
    if(!tFlag)
        fprintf(stderr, "No se ha especificado el numero de threads con -t.\n");
    if(!iFlag)
        fprintf(stderr, "No se ha especificado el archivo con los vectores con -i.\n");
    if(!oFlag)
        fprintf(stderr, "No se ha especificado el archivo de resultado con -o.\n");
    if(!tFlag || !iFlag || !oFlag){
        fprintf(stderr, HELP_MSG);
        exit(PARAMETER_ERROR);
    }
}

void ayuda()
{
    printf("\nAyuda:\n");
    printf("    El programa lee los pares pertenecientes a dos vectores desde un archivo y los suma dejando el vector resultante en otro archivo\n");
    printf("    Ejecutar con los siguientes parametros:\n");
    printf("        -i : Ruta del archivo a leer entre comillas\n");
    printf("        -o : Ruta del archivo a escribir entre comillas\n");
    printf("        -t : Cantidad de Threads\n");
}
