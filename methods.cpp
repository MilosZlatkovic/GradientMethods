#include "methods.hpp"
#include <math.h>
#include <stdlib.h>

double norm(Matrix& a)
{
  double sum = 0.0;

  for(unsigned i = 0; i < a.getRowsSize(); i++)
    sum += a[i][0]*a[i][0];

  return sqrt(sum);
}

Matrix ConjugateGradientMethod(Matrix& _A, Matrix& _b, Matrix& _X, double _tol, unsigned _maxIter)
{
  Matrix f, f0, l, l0, d, d0, mi, pom, pom1;
  
  if(!isSymmetric(_A))
    {
      cout << "Matrix is not symmetric!" << endl;
      exit(1);
    }

  f0 = _A * _X - _b;
  d0 = uminus(f0);    	
  
  pom = f0.transpose() * d0;

  l0 = uminus(pom) * Inv(d0.transpose() * _A * d0);
  _X = _X + l0*d0;
  d = d0;

  for(unsigned i = 1; i <= _maxIter; i++)
    {
      f = _A*_X - _b;
    
      if(norm(f) < _tol)
	return _X;

      mi = (f.transpose() * _A * d) * Inv(d.transpose() * _A * d);
  
      d = mi*d - f;

      Matrix pom1 = f.transpose() * d;
      l = (uminus(pom1))*Inv(d.transpose() * _A * d);

      _X = _X + l*d;      
    }

  return _X;
}


Matrix GradientDescentMethod(Matrix& _A, Matrix& _b, Matrix& _X, double _tol, unsigned _maxIter)
{
  Matrix f,l;
  
  if(!isSymmetric(_A))
    {
      cout << "Matrix is not symmetric!" << endl;
      exit(1);
    }

  for(unsigned i = 1; i <= _maxIter; i++)
    {
      f = _A*_X - _b;
    
      if(norm(f) < _tol)
	return _X;
  
      l = f.transpose() * f * Inv(f.transpose() * _A * f);

      _X = _X - l*f;      
    }

  return _X;
}


Matrix GradientDescentWithFixedStepSize(Matrix& _A, Matrix& _b, Matrix& _X, double _tol, unsigned _maxIter, double _alpha)
{
  Matrix f;
  
  if(!isSymmetric(_A))
    {
      cout << "Matrix is not symmetric!" << endl;
      exit(1);
    }

  for(unsigned i = 1; i <= _maxIter; i++)
    {
      f = _A*_X - _b;
    
      if(norm(f) < _tol)
	return _X;
  
      _X = _X - f*_alpha;      
    }

  return _X;
}
