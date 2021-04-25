/*!
 * @file TimeScheme.h
 *
 * @brief Defines classes for time integration.
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


#ifndef TIME_SCHEME_H
#define TIME_SCHEME_H

#include "MPIUtils.h"
#include "DataFile.h"
#include "Function.h"
#include "Laplacian.h"
#include "Vector.h"
#include <string>

class TimeScheme
{
protected:
  // Pointeur vers les trucs importants
  DataFile* _DF;
  Function* _function;
  Laplacian* _laplacian;

  // Solution
  DVector _Sol;
  
  // Paramètres de temps
  double _timeStep;
  double _initialTime;
  double _finalTime;
  double _currentTime;

  // Sauvegarde des résultats
  std::string _resultsDir;
  std::string _resFileName;
  
public:
  // Constructeurs
  TimeScheme();
  TimeScheme(DataFile* DF, Function* function, Laplacian* laplacian);

  // Initialiseur
  void Initialize(DataFile* DF, Function* function, Laplacian* laplacian);
  // Destructeur
  virtual ~TimeScheme() = default;

  // Getters
  const DVector& getSolution() const {return _Sol;};
  double getTimeStep() const {return _timeStep;};
  double getInitialTime() const {return _initialTime;};
  double getFinalTime() const {return _finalTime;};
  double getCurrentTime() const {return _currentTime;};
  
  // Solve and save solution
  virtual void oneStep() = 0;
  void saveCurrentSolution(std::string& fileName) const;
  void solve();

  // Compute the L2 error norm
  double computeCurrentError();
};

class ExplicitEuler: public TimeScheme
{
public:
  // Constructeurs
  ExplicitEuler();
  ExplicitEuler(DataFile* DF, Function* function, Laplacian* laplacian);

  // Initialiseur
  void Initialize(DataFile* DF, Function* function, Laplacian* laplacian);

  // One time step
  void oneStep();
};


class ImplicitEuler: public TimeScheme
{
public:
  // Constructeurs
  ImplicitEuler();
  ImplicitEuler(DataFile* DF, Function* function, Laplacian* laplacian);

  // Initialiseur
  void Initialize(DataFile* DF, Function* function, Laplacian* laplacian);

  // One time step
  void oneStep();
};

#endif // TIME_SCHEME_H
