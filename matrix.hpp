#ifndef __MATRIX_HPP__
#define __MATRIX_HPP__1

#include <iostream>
#include <vector>

using namespace std;

class Matrix
{
public:
  Matrix() {}
   
  Matrix(unsigned rows, unsigned cols);
                          
  ~Matrix();
 
  vector<double>& operator[](int i);
  vector<double> operator[](int i) const ;  
  Matrix& operator=(const Matrix& a);
  Matrix operator+(const Matrix& a);
  Matrix operator-(const Matrix& a);
  Matrix operator*(const Matrix& a);
  Matrix operator*(const double a);
 
  Matrix transpose() const;
  Matrix Minor(const unsigned row, const unsigned col) const;
  void Write(ostream& s) const; 

  unsigned getRowsSize() const;
  unsigned getColsSize() const;

private:
  vector<vector <double> > _m;
  unsigned _rows;
  unsigned _cols;
};

ostream& operator << (ostream& s, Matrix m);

Matrix Eye(const int n);

double Det(const Matrix& a);

Matrix Inv(const Matrix& a);

bool isSymmetric(const Matrix& a);

Matrix uminus(Matrix& a);

#endif
