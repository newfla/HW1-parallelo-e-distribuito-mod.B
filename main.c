#include <stdio.h>
#include <Utility/utilityMPI.h>
#include <Utility/utility.h>
int main(int argc, char *argv[]){

    int idProc=0,
        nProc=0,
        coords[2],
        *dims;
    MPI_Comm gridComm, rowComm, colComm;
    initMPIEnvironment(argc,argv,&nProc,&idProc);

    dims=find_best_value_for_grid(4);

    printf("%d %d",dims[0],dims[1]);

    createGridProc(dims[0],dims[1],coords,&gridComm);
    splitGrid(gridComm,&rowComm,&colComm);

    printf("Hello, World %d,%d!\n",coords[0],coords[1]);

    finalizeMPIEnvironment();

    return 0;
}