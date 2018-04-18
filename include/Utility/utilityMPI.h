//
// Created by bizzi on 18/04/18.
//

#ifndef HW1_UTILITYMPI_H
#define HW1_UTILITYMPI_H

#include <mpi.h>
void initMPIEnvironment(int argc, char** argv, int* nProc, int * idProc);

void finalizeMPIEnvironment();

void createGridProc(int row, int col, int* coords, MPI_Comm* grid);

void splitGrid(MPI_Comm grid, MPI_Comm*row,MPI_Comm*col);

#endif //HW1_UTILITYMPI_H
