//
// Created by bizzi on 18/04/18.
//

#include "utilityMPI.h"

void initMPIEnvironment(int argc, char** argv, int* nProc, int * idProc){
    int status=MPI_Init(&argc,&argv);
    if (status!=MPI_SUCCESS)
        return;
    MPI_Comm_rank(MPI_COMM_WORLD,idProc);
    MPI_Comm_size(MPI_COMM_WORLD,nProc);
}

void matrixBroadcast(MPI_Comm comm, int proc, int lda, int n, int m, double A[][lda]){
    double tmp[n][m];
    int myid;

    MPI_Comm_rank(comm, &myid);

    if(proc==myid) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                tmp[i][j] = A[i][j];
            }
        }
    }

    MPI_Bcast(tmp, n*m, MPI_DOUBLE,proc, comm);

    if(myid!=proc){
        for(int i=0;i<n;i++){
            for(int j=0;j<m;j++){
                A[i][j]=tmp[i][j];
            }
        }
    }
}

void finalizeMPIEnvironment(){
    MPI_Finalize();
}

void createGridProc(int row, int col, int* coords, MPI_Comm* grid){
    int period[]={1,1},
        dims[]={row,col},
        gridRank=0,
        status=MPI_Cart_create(MPI_COMM_WORLD,2,dims,period,1,grid);
    if (status!=MPI_SUCCESS)
        return;
    MPI_Comm_rank(*grid,&gridRank);
    MPI_Cart_coords(*grid,gridRank,2,coords);
}

void splitGrid(MPI_Comm grid, MPI_Comm*row,MPI_Comm*col){
    int remain[]={0,1};
    MPI_Cart_sub(grid,remain,row);
    remain[0]=1;
    remain[1]=0;
    MPI_Cart_sub(grid,remain,col);
}

double takeStartTime(MPI_Comm comm){
    MPI_Barrier(comm);
    return MPI_Wtime();
}

double takeEndTime(MPI_Comm comm){
    double localEndTime=0, endTime=0;
    localEndTime=MPI_Wtime();
    MPI_Reduce(&localEndTime,&endTime,1,MPI_DOUBLE,MPI_MAX,0,comm);
    //TODO ma in cosa misura Wtime???
    return endTime;
}