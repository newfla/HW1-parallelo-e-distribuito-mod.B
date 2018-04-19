#include <stdio.h>
#include <Utility/utilityMPI.h>
#include <Utility/utility.h>
#include <stdlib.h>

#define nThreads 8

int main(int argc, char *argv[]){


    //Sezione dichiarazione variabili
    int idProc=0,
        nProc=0,
        coords[2],
        N=128,
        *dims;

    double *A,*B,*C,
            startTime, endTime;

    char *firstLine="Nodes;Threads;Dimension;Time",
            *fileName=NULL,//="../Test.csv";
         result[50];

    MPI_Comm gridComm, rowComm, colComm;

    //-----------------------------------


    //Inizializzazione ambiente MPI

    initMPIEnvironment(argc,argv,&nProc,&idProc);

    dims=find_best_value_for_grid(nProc);

    createGridProc(dims[0],dims[1],coords,&gridComm);

    splitGrid(gridComm,&rowComm,&colComm);


    //-----------------------------------


    //Preparazione matrici

    N=atoi(argv[1]); //TODO nel cluster sarà argv[0]???
    A=(double*)calloc(N*N, sizeof(double));
    B=(double*)calloc(N*N, sizeof(double));
    C=(double*)calloc(N*N, sizeof(double));

    fill_vector(A,N*N);
    fill_vector(B,N*N);

    //-----------------------------------

    printf("Hello, World %d,%d///%d!\n",coords[0],coords[1],N);

    //Presa tempo di inizio

    startTime=takeStartTime(gridComm);

    // TODO PARTE DI CALCOLO

    //-----------------------------------

    //Presa tempo finale e stampa da parte di P0
    endTime=takeEndTime(gridComm);
    if (idProc==0) {
        clean_file(fileName);
        append_to_file(fileName,firstLine);
        sprintf(result,"%d;%d;%d;%.2f",nProc,nThreads,N*nProc,endTime);
        append_to_file(fileName,result);
    }

    //-----------------------------------

    //Uscita da ambiente MPI

    finalizeMPIEnvironment();

    return 0;
}