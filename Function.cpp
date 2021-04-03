#include "Function.h"
#include "DataFile.h"
#include "termcolor.h"
#include "Vector.h"

#include <cmath>

//--------------------------------------------------//
//--------------------Base Class--------------------//
//--------------------------------------------------//
Function::Function()
{
}

Function::Function(DataFile* DF):
  _DF(DF), _xmin(DF->getxMin()), _ymin(DF->getyMin()), _xmax(DF->getxMax()), _ymax(DF->getyMax()), _Lx(DF->getLx()), _Ly(DF->getLy()), _dx(_DF->getDx()), _dy(_DF->getDy()), _Nx(DF->getNx()), _Ny(DF->getNy()), _Sol0(_Nx * _Ny), _sourceTerm(_Nx * _Ny)
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
  _Sol0.resize(_Nx * _Ny);
  _sourceTerm.resize(_Nx * _Ny);
  this->Initialize();
}

void Function::Initialize()
{
  // Logs de début
  std::cout << "====================================================================================================" << std::endl;
  std::cout << "Building initial condition..." << std::endl;

  // Condition initiale
  _Sol0.resize(_Nx * _Ny, 1.);
  
  // Logs de fin
  std::cout << termcolor::green << "SUCCESS::FUNCTION : Initial Condition was successfully built." << std::endl;
  std::cout << termcolor::reset << "====================================================================================================" << std::endl << std::endl;
}

void Function::buildSourceTerm(double t)
{
  double D(_DF->getDiffCoeff());
  // Terme source
  for (int i(0) ; i < _Nx ; ++i)
    {
      for (int j(0) ; j < _Ny ; ++j)
        {
          _sourceTerm[i + j * _Nx] = f(_xmin + i * _dx, _ymin + j * _dy, t);
        }
    }

  // Ajout des conditions aux limites
  // Bas et haut
  for (int i(0) ; i < _Nx ; ++i)
    {
      _sourceTerm[i] += D * g(_xmin + i * _dx, _ymin, t) / pow(_dy, 2);
      _sourceTerm[i + (_Ny-1) * _Nx] += D * g(_xmin + i * _dx, _ymax, t) / pow(_dy, 2);
    }
  // Droite et gauche
  for (int j(0) ; j < _Ny ; ++j)
    {
      _sourceTerm[j * _Nx] += D * h(_xmin, _ymin + j * _dy, t) / pow(_dx, 2);
      _sourceTerm[_Nx - 1 + j * _Nx] += D * h(_xmax, _ymin + j * _dy, t) / pow(_dx, 2);
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
