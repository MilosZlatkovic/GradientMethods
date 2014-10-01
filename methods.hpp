#ifndef __METHODS_HPP__
#define __METHODS_HPP__1

#include <vector>
#include "matrix.hpp"

using namespace std;

double norm(Matrix& a);

Matrix ConjugateGradientMethod(Matrix& _A, Matrix& _b, Matrix& _X, double _tol, unsigned _maxIter);

Matrix GradientDescentMethod(Matrix& _A, Matrix& _b, Matrix& _X, double _tol, unsigned _maxIter);

Matrix GradientDescentWithFixedStepSize(Matrix& _A, Matrix& _b, Matrix& _X, double _tol, unsigned _maxIter, double _alpha);

#endif
