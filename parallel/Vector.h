/*!
 * @file Vector.h
 *
 * @brief Define a Vector class.
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


#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>

// Classe de vecteur pratique pour les opérations élémentaires
class DVector: public std::vector<double>
{
public:
  // Constructors
  DVector();
  DVector(size_type count);

  // Additional methods
  DVector add(const DVector& vec);
  DVector sub(const DVector& vec);
  double dot(const DVector& vec);

  // Print the vector (for debugging purpose)
  void print() const;
};

std::ostream& operator<< (std::ostream &os, const DVector& v);
DVector operator+ (const DVector& u, const DVector& v);
DVector operator- (const DVector& u, const DVector& v);
DVector operator* (double alpha, const DVector& u);
DVector operator* (const DVector& u, double alpha);

#endif //VECTOR_H
