#include "Function.h"
#include "MPIUtils.h"
#include "DataFile.h"
#include "termcolor.h"
#include "Vector.h"

#include <cmath>
#include <fstream>

//--------------------------------------------------//
//--------------------Base Class--------------------//
//--------------------------------------------------//
Function::Function()
{
}

Function::Function(DataFile* DF):
  _DF(DF), _xmin(DF->getxMin()), _ymin(DF->getyMin()), _xmax(DF->getxMax()), _ymax(DF->getyMax()), _Lx(DF->getLx()), _Ly(DF->getLy()), _dx(_DF->getDx()), _dy(_DF->getDy()), _Nx(DF->getNx()), _Ny(DF->getNy()), _Sol0(localSize), _sourceTerm(localSize), _exactSol(localSize)
{
}

void Function::Initialize(DataFile* DF)
{
  _DF = DF;
  _xmin = DF->getxMin();
  _ymin = DF->getyMin();
  _xmax = DF->getxMax();
  _ymax = DF->getyMax();
  _Lx = DF->getLx();
  _Ly = DF->getLy();
  _dx = DF->getDx();
  _dy = DF->getDy();
  _Nx = DF->getNx();
  _Ny = DF->getNy();
  _Sol0.resize(localSize);
  _sourceTerm.resize(localSize);
  _exactSol.resize(localSize);
  this->Initialize();
}

void Function::Initialize()
{
  // Logs de début
  if (MPI_Rank == 0)
    {
      std::cout << "====================================================================================================" << std::endl;
      std::cout << "Building initial condition..." << std::endl; 
    }
  
  // Resize la CI, le terme source et la solution exacte
  _Sol0.resize(localSize);
  _sourceTerm.resize(localSize);
  _exactSol.resize(localSize);
  for (int i(0) ; i < localSize ; ++i)
    {
      _Sol0[i] = 1.;
    }

  // Logs de fin
  if (MPI_Rank == 0)
    {
      std::cout << termcolor::green << "SUCCESS::FUNCTION : Initial Condition was successfully built." << std::endl;
      std::cout << termcolor::reset << "====================================================================================================" << std::endl << std::endl; 
    }
}

void Function::buildSourceTerm(double t)
{
  double D(_DF->getDiffCoeff());
  // Terme source
  for (int k(kBegin) ; k <= kEnd ; ++k)
    {
      // Intérieur du domaine
      int i(k%_Nx), j(k/_Nx);
      _sourceTerm[k - kBegin] = f(_xmin + i * _dx, _ymin + j * _dy, t);
      // Conditions aux limites
      // Bord bas
      if (j == 0)
        {
          _sourceTerm[k - kBegin] += D * g(_xmin + i * _dx, _ymin, t) / pow(_dy, 2);
        }
      // Bord haut
      else if (j == _Ny - 1)
        {
          _sourceTerm[k - kBegin] += D * g(_xmin + i * _dx, _ymax, t) / pow(_dy, 2);
        }
      // Bord gauche
      if (i == 0)
        {
          _sourceTerm[k - kBegin] += D * h(_xmin, _ymin + j * _dy, t) / pow(_dx, 2);
        }
      // Bord droit
      else if (i == _Nx - 1)
        {
          _sourceTerm[k - kBegin] += D * h(_xmax, _ymin + j * _dy, t) / pow(_dx, 2);
        }
    }
}


void Function::saveCurrentExactSolution(std::string &fileName) const
{
  std::ofstream outputFile(fileName, std::ios::out);
  outputFile.precision(10);

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
          outputFile << _exactSol[i+j*Nx] << " ";
        }
      outputFile << std::endl;
    }
}


//--------------------------------------------------//
//--------------------Function 1--------------------//
//--------------------------------------------------//
Function1::Function1():
  Function()
{
}

Function1::Function1(DataFile* DF):
  Function(DF)
{
}

double Function1::f(const double x, const double y, const double t)
{
  return 2*(y-y*y+x-x*x);
}

double Function1::g(const double x, const double y, const double t)
{
  return 0.;
}

double Function1::h(const double x, const double y, const double t)
{
  return 0.;
}

void Function1::buildExactSolution(double t)
{
  for (int k(kBegin) ; k <= kEnd ; ++k)
    {
      int i(k%_Nx), j(k/_Nx);
      double x(_xmin + i * _dx), y(_ymin + j * _dy);
      _exactSol[k - kBegin] = x*(1-x)*y*(1-y);
    }
}


//--------------------------------------------------//
//--------------------Function 2--------------------//
//--------------------------------------------------//
Function2::Function2():
  Function()
{
}

Function2::Function2(DataFile* DF):
  Function(DF)
{
}

double Function2::f(const double x, const double y, const double t)
{
  return sin(x) + cos(y);
}

double Function2::g(const double x, const double y, const double t)
{
  return sin(x) + cos(y);
}

double Function2::h(const double x, const double y, const double t)
{
  return sin(x) + cos(y);
}

void Function2::buildExactSolution(double t)
{
  for (int k(kBegin) ; k <= kEnd ; ++k)
    {
      int i(k%_Nx), j(k/_Nx);
      double x(_xmin + i * _dx), y(_ymin + j * _dy);
      _exactSol[k - kBegin] = sin(x) + cos(y);
    }
}


//--------------------------------------------------//
//--------------------Function 3--------------------//
//--------------------------------------------------//
Function3::Function3():
  Function()
{
}

Function3::Function3(DataFile* DF):
  Function(DF)
{
}

double Function3::f(const double x, const double y, const double t)
{
  return exp(-pow(x - 0.5 * _Lx, 2)) * exp(-pow(y - 0.5 * _Ly, 2)) * cos(0.5 * M_PI * t);
}

double Function3::g(const double x, const double y, const double t)
{
  return 0.;
}

double Function3::h(const double x, const double y, const double t)
{
  return 1.;
}

void Function3::buildExactSolution(double t)
{
  _exactSol.resize(localSize, 0.);
}
