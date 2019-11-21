#include "log.h"

void logInit(){
	FILE* fAux = fopen("/tmp/initLog", "w");
	char initLogMsg[] = "Successful init of Daemon...\n";
        fwrite(initLogMsg, sizeof(initLogMsg), 1, fAux);
	fclose(fAux);
}

void logMsg(char* msg){
	FILE* fpLog = fopen("/tmp/log", "a");
	fwrite(msg, strlen(msg), 1, fpLog);
	fclose(fpLog);
}