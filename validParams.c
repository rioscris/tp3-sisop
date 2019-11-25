#include "validParams.h"

void validParams(int argc, char** argv, char* pathToFile, char* fifoIn, char* fifoOut, char* log, const char* defaultLog){
    int index; 
    char option;
    int pFlag = 0;
    int iFlag = 0;
    int oFlag = 0;
    if (argc == 1) {
        fprintf(stdout, "Para correr el demonio se necesita especificar el <path> de datos, FIFO de entrada y FIFO de salida\n");
        fprintf(stderr, HELP_MSG);
        exit(PARAMETER_ERROR);
    }
    while ((option = getopt (argc, argv, ":p:hi:o:l:")) != -1)
        switch (option)
        {
            case 'h':
                mostrarAyuda(defaultLog);
                exit(ON_HELP_DISPLAY);
            case 'p':
                toggle(pFlag);

                /* La funcion realpath permite obtener la ruta absoluta para el parametro pasado. */
                /* En caso de recibir como ruta un directorio, e.g., './', la funcion 'realpath(..)' devolvera
                la ruta absoluta al directorio sin el '/' que denote que efectivamente se trata de un directorio, e.g., '/home'.
                Dado este resultado, podria tomarse como valido el archivo 'home' dentro de '/', sin embargo
                no puede existir dicho archivo por existir un directorio con el mismo nombre, con lo que la validacion de que
                este archivo efectivamente no existe se realizara en las instrucciones posteriores en el programa,
                en donde se necesite utilizarlo, i.e. fopen(..) == NULL*/
		        if(realpath(optarg, pathToFile)){
                    // Validacion de permiso de lectura para archivo
                    if(!access(pathToFile, R_OK))
                        fprintf(stdout, "Recibido el archivo de datos:\n%s\n\n", pathToFile);
                    else{
                        fprintf(stderr, "El archivo recibido no tiene permisos de lectura:\n%s\n\n", pathToFile);
                        fprintf(stderr, HELP_MSG);
                        exit(PARAMETER_ERROR);
                    }
                }
                else{
                    fprintf(stderr, "No se ha podido encontrar el archivo de datos:\n%s\n\n", pathToFile);
                    fprintf(stderr, HELP_MSG);
                    exit(PARAMETER_ERROR);
                }
                break;
            case 'i':
                toggle(iFlag);
                if(realpath(optarg, fifoIn)){
                    // Validacion de permiso de escritura para fifo
                    if(!access(fifoIn, W_OK))
                        fprintf(stdout, "Recibido el fifo de entrada: %s\n\n", fifoIn);
                    else{
                        fprintf(stderr, "El fifo recibido no tiene permisos de escritura:\n%s\n\n", fifoIn);
                        fprintf(stderr, HELP_MSG);
                        exit(PARAMETER_ERROR);
                    }
                }
                break;
            case 'o':
                toggle(oFlag);
                if(realpath(optarg, fifoOut)){
                    // Validacion de permiso de escritura para fifo
                    if(!access(fifoOut, W_OK))
                        fprintf(stdout, "Recibido el fifo de salida: %s\n\n", fifoOut);
                    else{
                        fprintf(stderr, "El fifo recibido no tiene permisos de escritura:\n%s\n\n", fifoOut);
                        fprintf(stderr, HELP_MSG);
                        exit(PARAMETER_ERROR);
                    }
                }
                break;
            case 'l':
                strcpy(log, optarg);
                break;
            case ':':
                if(optopt == 'p'){
                    fprintf(stderr, "No se ha recibido ningun parametro <path> para la opcion -p\n");
		            fprintf(stderr, "Por favor, especifique la ubicacion del archivo de datos\n");
		        }
                else if(optopt == 'i'){
                    fprintf(stderr, "No se ha recibido ningun parametro <path> para la opcion -i\n");
		            fprintf(stderr, "Por favor, especifique la ubicacion del FIFO de entrada\n");
		        }
                else if(optopt == 'o'){
                    fprintf(stderr, "No se ha recibido ningun parametro <path> para la opcion -o\n");
		            fprintf(stderr, "Por favor, especifique la ubicacion del FIFO de salida\n");
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
    if(!pFlag)
        fprintf(stderr, "No se ha especificado el archivo de datos con -p\n");
    if(!iFlag)
        fprintf(stderr, "No se ha especificado el FIFO de entrada con -i\n");
    if(!oFlag)
        fprintf(stderr, "No se ha especificado el FIFO de salida con -o\n");
    if(!pFlag || !iFlag || !oFlag){
        fprintf(stderr, HELP_MSG);
        exit(PARAMETER_ERROR);
    }
}