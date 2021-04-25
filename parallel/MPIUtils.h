/*!
 * @file MPIUtils.h
 *
 * @brief Defines the global MPI variables and a function to compute the load allocated to each MPI proc.
 *
 * @authors Gabriel Suau, Remi Pegouret, Geoffrey Lebaud
 *
 * @version 0.1.0
 *
 * @copyright © 2021 Gabriel Suau
 * @copyright © 2021 Remi Pegouret
 * @copyright © 2021 Geoffrey Lebaud
 * 
 * @copyright This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * @copyright This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * @copyright You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/

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
