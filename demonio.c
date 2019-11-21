#include "demonio.h"

void createDemon(pid_t* p_id, pid_t* c_id, pid_t* s_id){
    *p_id = fork();

    if(*p_id < 0){
        fprintf(stderr, "Error en creacion de proceso... Codigo de error: %d\n", errno);
        exit(ON_FORK_ERROR);
    }
    if(*p_id > 0){
        fprintf(stdout, "Proceso padre finalizado exitosamente!\n");
        exit(TERMINATE_PARENT_PROCESS);
    }

    umask(0);

    *c_id = getpid();
    *s_id = setsid();
    
    if(*s_id < 0){
        fprintf(stderr, "Error en creacion de sesion... Codigo de error: %d\n", errno);
        exit(ON_SESSION_ERROR);
    }

    fprintf(stdout, "Proceso hijo creado exitosamente. PID: %d\n", getpid());

    chdir("/");
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
}