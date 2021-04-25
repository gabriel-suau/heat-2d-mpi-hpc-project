/*!
 * @file Laplacian.h
 *
 * @brief Defines a class representing the discrete laplacian matrix.
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


#ifndef LAPLACIAN_H
#define LAPLACIAN_H

#include "MPIUtils.h"
#include "DataFile.h"
#include "Function.h"
#include "Vector.h"
#include <fstream>

class Laplacian
{
private:
  // Pointeurs vers les trucs importants
  DataFile* _DF;
  Function* _function;
  
  // Coefficients de la matrice du laplacien 2D
  double _alpha, _beta, _gamma;
  int _Nx, _Ny;
  
public:
  // Constructeurs
  Laplacian();
  Laplacian(DataFile* DF, Function* function);

  // Destructeur
  ~Laplacian() = default;

  // Initialisation
  void Initialize();
  void Initialize(DataFile* DF, Function* function);
  
  // Getters
  double getAlpha() const {return _alpha;};
  double getBeta() const {return _beta;};
  double getGamma() const {return _gamma;};
  int getNx() const {return _Nx;}
  int getNy() const {return _Ny;};
  
  // Produit matVec et GC
  DVector matVecProd(const DVector& x);
  DVector solveConjGrad(const DVector& b, const DVector& x0, double tolerance, int maxIterations, std::ofstream& resFile);
  
  // Printer (pour debugger)
  void print() const;
};

#endif // LAPLACIAN_H
