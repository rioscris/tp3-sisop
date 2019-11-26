#include <sys/stat.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unwind.h>
#include <unistd.h>
#include <errno.h>

#define ON_FORK_ERROR 1
#define TERMINATE_PARENT_PROCESS 0
#define ON_SESSION_ERROR 2

void createDemon(pid_t*, pid_t*, pid_t*);