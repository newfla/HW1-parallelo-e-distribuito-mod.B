//
// Created by bizzi on 20/04/18.
//

#include "mat_mat_distributed.h"
#include "mat_mat.h"
#include "../Utility/utilityMPI.h"
#include "stdio.h"


void SUMMA(MPI_Comm rowComm, MPI_Comm colComm, int rowId, int colId, int nThreads, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda],
           double B[][ldb], double C[][ldc]){
    int nRow,
        nCol;

    double A2[n][m], B2[m][p];
    double **Acalc=NULL, **Bcalc=NULL;
    int ldacalc, ldbcalc;

    MPI_Comm_size(rowComm, &nRow);
    MPI_Comm_size(colComm, &nCol);
    //printf("row:%d-col:%d\n",nRow,nCol);

    for(int k=0; k<nRow; k++){

        //broadcast A[rowId][k] su riga rowId
        if(k==colId){
            //broadcast mia matrice verso gli altri
            matrixBroadcast(rowComm, k, lda, n, m, A);
            ldacalc = lda;
            Acalc = A;
        }else{
            //ricevo mia matrice da processore k di riga
            matrixBroadcast(rowComm, k, lda, n, m, A2);
            ldacalc = m;
            Acalc = A2;
        }

        //printf("Valore K %d-valore maxColCOmm  %d\n",k, nCol);
        //broadcast B[k][colId] su colonna colId
        if(k==rowId){

            matrixBroadcast(colComm, k, ldb, m, p, B);
            ldbcalc = ldb;
            Bcalc = B;
        }else{
            matrixBroadcast(colComm, k, ldb, m, p, B2);
            /*TODO il problema è questo Bcast. Aspetto dal proc con id=3 su colCOmm che ha dim=2*/
            ldbcalc = p;
            Bcalc = B2;
        }

        mat_mat_threads(nThreads, 1, n, m, p, ldacalc, ldbcalc, ldc, (double(*)[]) Acalc, (double(*)[])Bcalc, C);
    }
}
