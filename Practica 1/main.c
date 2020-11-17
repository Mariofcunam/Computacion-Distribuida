#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <mpi.h>
#include "GeneralesBizantinos.h"

int main(int argc, char *argv[]){
    srand(time(NULL));


int rango;

int num_procesos;

MPI_Init(&argc, $argv);
MPI_Comm_rank(MPI_COMM_WORLD, &rango);
MPI_Comm_size(MPI_COMM_WORLD, &num_procesos);

int decision_final=ponerse_acuerdo(rango,num_procesos);

printf("Proceso num [%d el cual fue la decision fue tomada con el valor %d\n", rango, decision_final);

MPI_Finaliza();
return 0;
}