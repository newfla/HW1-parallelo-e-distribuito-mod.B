//
// Created by bizzi on 20/04/18.
//

#include "mat_mat_distributed.h"
#include "mat_mat.h"


void SUMMA(MPI_Comm rowComm, MPI_Comm colComm, int rowId, int colId, int nThreads, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda],
           double B[][ldb], double C[][ldc]){
    int nRow,
        nCol;

    double A2[n][m], B2[m][p];
    double **Acalc, **Bcalc;

    MPI_Comm_size(rowComm, &nRow);
    MPI_Comm_size(colComm, &nCol);



    for(int k=0; k<nRow; k++){
        //broadcast A[rowId][k] su riga rowId
        if(k==colId){
            //broadcast mia matrice verso gli altri
            MPI_Bcast()
            Acalc = A;
        }else{
            //ricevo mia matrice da processore k di riga
            Acalc = A2;
        }

        //broadcast B[k][colId] su colonna colId
        if(k==rowId){

            Bcalc = B;
        }else{

            Bcalc = B2;
        }

        mat_mat_threads(nThreads, 1, n, m, p, lda, ldb, ldc, Acalc, Bcalc, C);
    }
}
