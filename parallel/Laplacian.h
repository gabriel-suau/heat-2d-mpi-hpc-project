#ifndef LAPLACIAN_H
#define LAPLACIAN_H

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

  // MPI variables
  int _MPIRank, _MPISize;
  
public:
  // Constructeurs
  Laplacian();
  Laplacian(DataFile* DF, Function* function, int MPIRank, int MPISize);

  // Destructeur
  ~Laplacian() = default;

  // Initialisation
  void Initialize();
  void Initialize(DataFile* DF, Function* function, int MPIRank, int MPISize);
  
  // Getters
  double getAlpha() const {return _alpha;};
  double getBeta() const {return _beta;};
  double getGamma() const {return _gamma;};
  int getNx() const {return _Nx;}
  int getNy() const {return _Ny;};
  int getMPIRank() const {return _MPIRank;}
  int getMPISize() const {return _MPISize;};
  
  // Produit matVec et GC
  DVector matVecProd(const DVector& x);
  DVector solveConjGrad(const DVector& b, const DVector& x0, double tolerance, int maxIterations, std::ofstream& resFile);
  
  // Printer (pour debugger)
  void print() const;
};


// Répartit la charge avec un désiquilibre de charge <= 1
void charge(int N, int Np, int me, int& iBegin, int& iEnd)
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

#endif // LAPLACIAN_H
