//
// Created by bizzi on 20/04/18.
//
#include <mpi.h>

#ifndef HW1_MAT_MAT_DISTRIBUTED_H
#define HW1_MAT_MAT_DISTRIBUTED_H

void SUMMA(MPI_Comm rowComm, MPI_Comm colComm, int rowId, int colId, int nThreads, int n, int m, int p, int lda, int ldb, int ldc, double A[][lda],
           double B[][ldb], double C[][ldc]);

#endif //HW1_MAT_MAT_DISTRIBUTED_H
