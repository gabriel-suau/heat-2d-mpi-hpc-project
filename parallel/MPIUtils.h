#ifndef MPI_UTILS_H
#define MPI_UTILS_H

#include <mpi.h>

// Global MPI variables
extern int MPI_Size, MPI_Rank, kBegin, kEnd, rowBegin, rowEnd, localSize, nbDomainRows;
extern MPI_Status status;

// Répartit la charge avec un désiquilibre de charge inferieur ou egal a 1
inline void charge(int N, int Np, int me, int& iBegin, int& iEnd)
{
  // Division entière
  int chargeMinParProc(N/Np);
  // Reste à répartir
  int reste(N%Np);

  if (me < reste)
    {
      iBegin = me * (chargeMinParProc + 1);
      iEnd = iBegin + chargeMinParProc;
    }
  else
    {
      iBegin = reste + me * chargeMinParProc;
      iEnd = iBegin + chargeMinParProc - 1;
    }
}

#endif // MPI_UTILS_H
