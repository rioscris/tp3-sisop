#define LINE_LEN 30
#define CON_MSJ 1
#define ON_FILE_ERROR -2
#define INVALID_DATA -3
#define PATH_LEN 300

typedef struct{
    double primero;
    double segundo;
}t_par;

typedef struct{
    FILE* filedst;
    FILE* filesrc;
    int cargaPThread;
}t_infoTh;