#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#include "validParams.h"
#include "ipc.h"
#include "demonio.h"
#include "stringExt.h"

#define PATH_LEN 150
#define FIFO_PERMISSIONS 0666
#define DEFAULT_LOGGER "./logger.txt"