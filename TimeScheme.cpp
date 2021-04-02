#include "TimeScheme.h"
#include "Vector.h"
#include "DataFile.h"
#include "Function.h"
#include "Laplacian.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

//--------------------------------------------------//
//--------------------Base Class--------------------//
//--------------------------------------------------//
TimeScheme::TimeScheme()
{
}

TimeScheme::TimeScheme(DataFile* DF, Function* function, Laplacian* laplacian):
  _DF(DF), _function(function), _laplacian(laplacian), _Sol(_function->getInitialCondition()), _timeStep(DF->getTimeStep()), _initialTime(DF->getInitialTime()), _finalTime(DF->getFinalTime()), _currentTime(_initialTime)
{
}

void TimeScheme::Initialize(DataFile* DF, Function* function, Laplacian* laplacian)
{
  _DF = DF;
  _function = function;
  _laplacian = laplacian;
  _Sol = _function->getInitialCondition();
  _timeStep = DF->getTimeStep();
  _initialTime = DF->getInitialTime();
  _finalTime = DF->getFinalTime();
  _currentTime = _initialTime;
}

void TimeScheme::saveCurrentSolution(std::string &fileName) const
{
  std::ofstream outputFile(fileName, std::ios::out);
  outputFile.precision(7);

  // Récupération des variables utiles
  int Nx(_DF->getNx()), Ny(_DF->getNy());
  double xmin(_DF->getxMin()), ymin(_DF->getyMin());
  double dx(_DF->getDx()), dy(_DF->getDy());

  outputFile << "# vtk DataFile Version 3.0" << std::endl;
  outputFile << "sol" << std::endl;
  outputFile << "ASCII" << std::endl;
  outputFile << "DATASET STRUCTURED_POINTS" << std::endl;
  outputFile << "DIMENSIONS " << Nx << " " << Ny << " " << 1 << std::endl;
  outputFile << "ORIGIN " << xmin << " " << ymin << " " << 0 << std::endl;
  outputFile << "SPACING " << dx << " " << dy << " " << 1 << std::endl;;
  outputFile << "POINT_DATA " << Nx*Ny << std::endl;
  outputFile << "SCALARS sol float" << std::endl;
  outputFile << "LOOKUP_TABLE default" << std::endl;

  for(int j=0; j<Ny; ++j)
    {
      for(int i=0; i<Nx; ++i)
        {
          outputFile << _Sol[i+j*Nx] << " ";
        }
      outputFile << std::endl;
    }
}

void TimeScheme::solve()
{
  // Logs de début
  std::cout << "====================================================================================================" << std::endl;
  std::cout << "Time loop..." << std::endl;

  // Variables pratiques
  int n(0);
  std::string resultsDir(_DF->getResultsDirectory());
  int scenario(_DF->getScenario());

  // Sauvegarde la condition initiale
  std::string fileName(resultsDir + "/solution_scenario_" + std::to_string(scenario) + "_" + std::to_string(n) + ".vtk");
  saveCurrentSolution(fileName);

  // Boucle en temps
  while (_currentTime < _finalTime)
    {
      oneStep();
      ++n;
      _currentTime += _timeStep;
      if (n % _DF->getSaveFrequency() == 0)
        {
          std::cout << "Saving solution at t = " << _currentTime << std::endl;
          std::string fileName(resultsDir + "/solution_scenario_" + std::to_string(scenario) + "_" + std::to_string(n) + ".vtk");
          saveCurrentSolution(fileName);
        }
    }

  // Logs de fin
  std::cout << termcolor::green << "SUCCESS::TIMESCHEME : Time loop completed successfully !" << std::endl;
  std::cout << termcolor::reset << "====================================================================================================" << std::endl << std::endl;
}


//-------------------------------------------------------------//
//--------------------Explicit Euler scheme--------------------//
//-------------------------------------------------------------//
ExplicitEuler::ExplicitEuler():
  TimeScheme()
{
}

ExplicitEuler::ExplicitEuler(DataFile* DF, Function* function, Laplacian* laplacian):
  TimeScheme(DF, function, laplacian)
{
}

void ExplicitEuler::Initialize(DataFile* DF, Function* function, Laplacian* laplacian)
{
  _DF = DF;
  _function = function;
  _laplacian = laplacian;
  _Sol = _function->getInitialCondition();
  _timeStep = DF->getTimeStep();
  _initialTime = DF->getInitialTime();
  _finalTime = DF->getFinalTime();
  _currentTime = _initialTime;
}

void ExplicitEuler::oneStep()
{
  // Récupération des trucs importants
  double dt(_timeStep);
  // Calcul du terme source
  _function->buildSourceTerm(_currentTime);
  // Calcul de la solution
  _Sol = _Sol + (_laplacian->matVecProd(_Sol) + dt * _function->getSourceTerm());
}


//-------------------------------------------------------------//
//--------------------Implicit Euler scheme--------------------//
//-------------------------------------------------------------//
ImplicitEuler::ImplicitEuler():
  TimeScheme()
{
}

ImplicitEuler::ImplicitEuler(DataFile* DF, Function* function, Laplacian* laplacian):
  TimeScheme(DF, function, laplacian)
{
}

void ImplicitEuler::Initialize(DataFile* DF, Function* function, Laplacian* laplacian)
{
  _DF = DF;
  _function = function;
  _laplacian = laplacian;
  _Sol = _function->getInitialCondition();
  _timeStep = DF->getTimeStep();
  _initialTime = DF->getInitialTime();
  _finalTime = DF->getFinalTime();
  _currentTime = _initialTime;
}

void ImplicitEuler::oneStep()
{
  // Récupération des trucs importants
  double dt(_timeStep);
  double tolerance(_DF->getTolerance());
  int maxIt(_DF->getMaxIterations());
  // Calcul du terme source
  _function->buildSourceTerm(_currentTime + dt);
  // Calcul de la solution
  _Sol = _laplacian->solveConjGrad(dt * _function->getSourceTerm(), _Sol, tolerance, maxIt);
}
