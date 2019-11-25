#include "log.h"

void logMessage(const char* message, const char* logger){
	if(strcmp(logger, "\0")){
		FILE* fpLog = fopen(logger, "a");
		if(fpLog){
			fwrite(message, strlen(message), 1, fpLog);
			fclose(fpLog);
		}
	}
}

void initLog(char* pathname, const char* defaultPath){
	char* initMsg = "-Inicio exitoso de demonio.\n";
	char* relativePath;
	FILE* fpLog;

	if(strcmp(pathname, "\0") == 0){
		fpLog = fopen(defaultPath, "w");
		if(fpLog){
			fprintf(stdout, "Inicio Logger en archivo por defecto: %s\n", defaultPath);
			fwrite(initMsg, strlen(initMsg), 1, fpLog);
			fclose(fpLog);
			strcpy(pathname, defaultPath);
		}
		else{
			fprintf(stdout, "Inicio sin Logger\n");
		}
	}
	else{
		relativePath = (char*)malloc(sizeof(pathname));
		if(relativePath != NULL){
			strcpy(relativePath, pathname);
			realpath(relativePath, pathname);
			fpLog = fopen(pathname, "w");
			if(fpLog){
				fprintf(stdout, "Inicio Logger en: %s\n", pathname);
				fwrite(initMsg, strlen(initMsg), 1, fpLog);
				fclose(fpLog);
			}
			else{
				fprintf(stderr, "No se ha podido iniciar el logger en el path especificado.\n");
				strcpy(pathname, "\0");
			}
		}
		else{
			fprintf(stderr, "No se ha podido iniciar el logger en el path especificado.\n");
			strcpy(pathname, "\0");
		}
		free(relativePath);
	}
}