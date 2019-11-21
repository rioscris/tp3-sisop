#include "stringExt.h"

void removeNewlineAtOffset(char* string, int offset){
    char* newLine = strrchr(string, '\n') + offset;
    if(newLine != NULL){
        *newLine = '\0';
    }
}