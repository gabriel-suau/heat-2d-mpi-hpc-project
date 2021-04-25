/*!
 * @file DataFile.h
 *
 * @brief DataFile class to read the simulation parameters.
 *
 * This file contains a DataFile class that reads the parameters file
 * and contains all the parameters of the simulation.
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


#ifndef DATA_FILE_H
#define DATA_FILE_H

#include "MPIUtils.h"
#include <string>

class DataFile
{
private:
  std::string _fileName;

  // Solution saving
  std::string _resultsDir;
  bool _isSaveFinalResultOnly;
  int _saveFrequency;

  // Scenario
  int _scenario;
  
  // Time parameters
  std::string _timeScheme;
  double _initialTime;
  double _finalTime;
  double _timeStep;
  double _CFL;

  // Spatial parameters
  double _xmin, _xmax, _ymin, _ymax;
  double _Lx, _Ly;
  int _Nx, _Ny;
  double _dx, _dy;

  // Linear solver parameters
  int _maxIterations;
  double _tolerance;
  bool _isSaveResidual;
  std::string _resFile;
  
  // Diffusion coefficient
  double _diffCoeff;
  
public:

  DataFile();
  DataFile(const std::string& fileName);

  ~DataFile() = default;

  void Initialize(const std::string& fileName);

  void readDataFile();

  // Getters
  // DataFile name
  const std::string& getFileName() const {return _fileName;};
  // Solution saving
  const std::string& getResultsDirectory() const {return _resultsDir;};
  bool isSaveFinalResultOnly() const {return _isSaveFinalResultOnly;};
  int getSaveFrequency() const {return _saveFrequency;};
  int getScenario() const {return _scenario;};
  // Time parameters
  const std::string& getTimeScheme() const {return _timeScheme;};
  double getInitialTime() const {return _initialTime;};
  double getFinalTime() const {return _finalTime;};
  double getTimeStep() const {return _timeStep;};
  double getCFL() const {return _CFL;};
  // Mesh parameters
  double getxMin() const {return _xmin;};
  double getxMax() const {return _xmax;}
  double getyMin() const {return _ymin;};
  double getyMax() const {return _ymax;};
  double getLx() const {return _Lx;};
  double getLy() const {return _Ly;};
  int getNx() const {return _Nx;};
  int getNy() const {return _Ny;};
  double getDx() const {return _dx;}
  double getDy() const {return _dy;};
  // Linear solver parameters
  int getMaxIterations() const {return _maxIterations;};
  double getTolerance() const {return _tolerance;};
  bool isSaveResidual() const {return _isSaveResidual;}
  std::string getResFile() const {return _resFile;};
  // Diffusion coefficient
  double getDiffCoeff() const {return _diffCoeff;};

  void printData() const;

protected:
  std::string cleanLine(std::string &line);
};

#endif // DATA_FILE_H
