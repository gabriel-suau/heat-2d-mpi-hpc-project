/*!
 * @file Vector.cpp
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


#include "Vector.h"
#include <vector>
#include <iostream>

// Constructors
DVector::DVector():
  std::vector<double>()
{
}


// Constructors
DVector::DVector(size_type count):
  std::vector<double>(count)
{
}

// Additional methods
DVector DVector::add(const DVector& vec)
{
  int N(vec.size());
  for (int i(0) ; i < N ; ++i)
    {
      this->operator[](i) += vec[i];
    }
  return *this;
}


DVector DVector::sub(const DVector& vec)
{
  int N(vec.size());
  for (int i(0) ; i < N ; ++i)
    {
      this->operator[](i) -= vec[i];
    }
  return *this;
}


double DVector::dot(const DVector& vec)
{
  int N(vec.size());
  double dot(0.);
  for (int i(0) ; i < N ; ++i)
    {
      dot += this->operator[](i) * vec[i];
    }
  return dot;
}


void DVector::print() const
{
  for (int i(0) ; i < this->size() ; ++i)
    {
      std::cout << this->operator[](i) << " ";
    }
  std::cout << std::endl << std::endl;
}


// Operators
std::ostream& operator<< (std::ostream &os, const DVector& v)
{
  int N(v.size());
  for (int i(0) ; i < N - 1 ; ++i)
    {
      os << v[i] << " ";
    }
  os << v[N-1] << std::endl;
  return os;
}

DVector operator+ (const DVector& u, const DVector& v)
{
  if (u.size() == v.size())
    {
      DVector w;
      w.resize(u.size());
      for (int i(0) ; i < u.size() ; ++i)
        {
          w[i] = u[i] + v[i];
        }
      return w;
    }
  else
    {
      std::cout << "ERROR : DVector sizes do not match (" << u.size() << " and " << v.size() << ")" << std::endl;
      exit(1);
    }
}

DVector operator- (const DVector& u, const DVector& v)
{
  if (u.size() == v.size())
    {
      DVector w;
      w.resize(u.size());
      for (int i(0) ; i < u.size() ; ++i)
        {
          w[i] = u[i] - v[i];
        }
      return w;
    }
  else
    {
      std::cout << "ERROR : DVector sizes do not match (" << u.size() << " and " << v.size() << ")" << std::endl;
      exit(1);
    }
}


DVector operator* (double alpha, const DVector& u)
{
  DVector w;
  w.resize(u.size());
  for (int i(0) ; i < u.size() ; ++i)
    {
      w[i] = alpha * u[i];
    }
  return w;
}


DVector operator* (const DVector& u, double alpha)
{
  DVector w;
  w.resize(u.size());
  for (int i(0) ; i < u.size() ; ++i)
    {
      w[i] = alpha * u[i];
    }
  return w;
}
