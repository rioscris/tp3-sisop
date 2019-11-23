#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "log.h"
#include "articulosFunc.h"

#define STR_LEN 300
#define MAX_HEADER_LEN 20
#define MAX_FILTER_VALUE_LEN 200
#define OPEN_MODE "r"
#define ON_OPEN_FILE_ERROR -1
#define MAX_FILTER_LENGTH 220

int searchInFile(char*, int*, char*);
void createFifos(char*, char*, mode_t);
void handleInputs(char*, char*, char*);
