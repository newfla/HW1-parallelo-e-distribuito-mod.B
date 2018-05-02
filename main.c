#include <stdio.h>
#include <Utility/utilityMPI.h>
#include <Utility/utility.h>
#include <stdlib.h>
#include <Mat_Mat/mat_mat_distributed.h>

int main(int argc, char *argv[]){


    //Sezione dichiarazione variabili
    int idProc=0,
        nProc=0,
        nThreads=1,
        coords[2],
        N=1,
        *dims=NULL;

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

    N=atoi(argv[1]);

    nThreads = atoi(argv[2]);
    A=(double*)calloc(N*N, sizeof(double));
    B=(double*)calloc(N*N, sizeof(double));
    C=(double*)calloc(N*N, sizeof(double));

    fill_vector(A,N*N);
    fill_vector(B,N*N);

    //-----------------------------------

    //Presa tempo di inizio

    startTime=takeStartTime(gridComm);

    SUMMA(rowComm, colComm, coords[0], coords[1], nThreads, N, N, N, N, N, N, (double(*)[])A, (double(*)[])B, (
    double(*)[])C);
    //-----------------------------------

    //Presa tempo finale e stampa da parte di P0
    endTime=takeEndTime(gridComm);
    endTime-=startTime;
    if (idProc==0) {
        clean_file(fileName);
        //append_to_file(fileName,firstLine);
        sprintf(result,"%d;%d;%d;%.5f",nProc,nThreads,N*nProc,endTime);
        append_to_file(fileName,result);
    }

    //-----------------------------------

    //Uscita da ambiente MPI
    free(A);
    free(B);
    free(C);
    finalizeMPIEnvironment();

    return 0;
}