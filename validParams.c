#include "validParams.h"

void validParams(int argc, char** argv, char* pathToFile){
    int index; 
    char option;
    
    if (argc == 1) {
        fprintf(stdout, "Para correr el demonio se necesita especificar el archivo de base de datos con el parametro -p <path>\n");
        fprintf(stdout, "Para recibir ayuda, ingrese el parametro -h\n");
        exit(PARAMETER_ERROR);
    }
    while ((option = getopt (argc, argv, ":p:h")) != -1)
        switch (option)
        {
            case 'h':
                mostrarAyuda();
                exit(ON_HELP_DISPLAY);
            case 'p':
		        if(realpath(optarg, pathToFile)){
                    /* La funcion realpath permite obtener la ruta absoluta para el parametro pasado. */
                    /* En caso de recibir como ruta un directorio, e.g., './', la funcion 'realpath(..)' devolvera
                    la ruta absoluta al directorio sin el '/' que denote que efectivamente se trata de un directorio, e.g., '/home'.
                    Dado este resultado, podria tomarse como valido el archivo 'home' dentro de '/', sin embargo
                    no puede existir dicho archivo por existir un directorio con el mismo nombre, con lo que la validacion de que
                    este archivo efectivamente no existe se realizara en las instrucciones posteriores en el programa,
                    en donde se necesite utilizarlo, i.e. fopen(..) == NULL*/
        
                    // Validacion de permiso de lectura para archivo
                    if(access(pathToFile, R_OK))
                        fprintf(stdout, "El archivo recibido no tiene permisos de lectura:\n%s\n\n", pathToFile);
                    else
                        fprintf(stdout, "Recibido el archivo de datos:\n%s\n\n", pathToFile);
                }
                else{
                    fprintf(stderr, "No se ha podido encontrar el archivo:\n%s\n\n", pathToFile);
                    fprintf(stderr, "Para recibir ayuda, ingrese el parametro -h\n");
                    exit(PARAMETER_ERROR);
                }
                break;
            case ':':
                if(optopt == 'p'){
                    fprintf(stderr, "No se ha recibido ningun parametro <path> para la opcion -p\n");
		            fprintf(stderr, "Por favor, especifique la ubicacion del archivo de datos\n");
		        }
                else{
		            fprintf(stderr, "Los parametros recibidos son incorrectos.\n");
                }
                fprintf(stderr, "Para recibir ayuda, ingrese el parametro -h\n");
                exit(PARAMETER_ERROR);
            case '?':
                fprintf(stderr, "No se reconoce la opcion %c\n", optopt);
                fprintf(stderr, "Para recibir ayuda, ingrese el parametro -h\n");
		        exit(PARAMETER_ERROR);
            default:
                exit(PARAMETER_ERROR);
        }
    for (index = optind; index < argc; index++){
        fprintf(stdout, "ERROR: Se ha recibido un parametro no reconocido: %s\n", argv[index]);
        fprintf(stderr, "Para recibir ayuda, ingrese el parametro -h\n");
        exit(PARAMETER_ERROR);
    }
}