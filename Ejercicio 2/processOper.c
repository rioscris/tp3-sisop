#include "processOper.h"

int calcularRestantesEnProceso(FILE* filesrc, FILE* filedst, const int cargaPProcess){
    t_par auxPar;
    char line[LINE_LEN];
    tInfoCalc auxInfoCalcProcess;
    
    for (int i = 0; i < cargaPProcess; i++)
    {
        if(!fgets(line, sizeof(line), filesrc))
            return REMAINING_CALC_ERROR;
        
        trozarCampos(&auxPar, line);
        auxInfoCalcProcess.primero = auxPar.primero;
        auxInfoCalcProcess.segundo = auxPar.segundo;
        calcular(&auxInfoCalcProcess);
        // printf("Desde el proceso, escribiendo el resultado %f\n", auxInfoCalcProcess.resultado);
        if(fprintf(filedst, "%f\n", auxInfoCalcProcess.resultado) < 0)
            return REMAINING_CALC_ERROR;
    }

    return OP_SUCESS;
}