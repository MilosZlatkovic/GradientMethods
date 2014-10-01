#include <iostream>
#include <iomanip>
#include <vector>
#include <cstdio>
#include "matrix.hpp"
#include <stdlib.h>
#include <math.h>

using namespace std;

Matrix::Matrix(unsigned rows, unsigned cols) 
{
  _m.resize(rows);
 
  for (unsigned k = 0; k < rows; k++) 
    _m[k].resize(cols);
  
  for (unsigned i = 0; i < rows; i++) 
    for (unsigned j = 0; j < cols; j++)
      _m[i][j] = 0.0;

  _rows = rows;
  _cols = cols;
}


Matrix::~Matrix() {}


vector<double>& Matrix::operator[](int i) 
{
  return _m[i];
}


vector<double> Matrix::operator[](int i) const 
{
  return _m[i];
}


Matrix& Matrix::operator=(const Matrix& a) 
{
  if(&a == this)
    return *this;

  unsigned new_rows = a.getRowsSize();
  unsigned new_cols = a.getColsSize();

  _m.resize(new_rows);

  for (unsigned k = 0; k < new_rows; k++) 
    _m[k].resize(new_cols);
 
  for (unsigned i = 0; i < new_rows; i++)
    for (unsigned j = 0; j < new_cols; j++)
      _m[i][j] = a[i][j];


  _rows = new_rows;
  _cols = new_cols;

  return *this;
}


Matrix Matrix::operator+(const Matrix& a) 
{
  if (_rows != a._rows || _cols != a._cols)
    {
      cout << "Improper dimensions" << endl;
      exit(1);
    }

  Matrix r (_rows, _cols);

  for (unsigned i = 0; i < _rows; i++)
    for (unsigned j = 0; j < _cols; j++)
      r[i][j] = (*this)[i][j] + a[i][j];

  return r;
}


Matrix Matrix::operator-(const Matrix& a)
{
  if (_rows != a._rows || _cols != a._cols)
    {
      cout << "Improper dimensions" << endl;
      exit(1);
    }

  Matrix r (_rows, _cols);

  for (unsigned i = 0; i < _rows; i++)
    for (unsigned j = 0; j < _cols; j++)
      r[i][j] = (*this)[i][j] - a[i][j];
  
  return r;
}


Matrix Matrix::operator*(const Matrix& a) 
{
  if(a._rows == 1 && a._cols == 1)
    {
      Matrix r(_rows, _cols);

      for (unsigned i = 0; i < _rows; i++)
	for (unsigned j = 0; j < _cols; j++)
	  r[i][j] = (*this)[i][j] * a[0][0];

      return r;
    }

  if(_rows == 1 && _cols == 1)
    {
      Matrix r(a._rows, a._cols);

      for (unsigned i = 0; i < a._rows; i++)
	for (unsigned j = 0; j < a._cols; j++)
	  r[i][j] = a[i][j] * (*this)[0][0];

      return r;
    }

  if (_cols != a._rows)
    {
      cout << "Improper dimensions" << endl;
      exit(1);
    }

  Matrix r (_rows, a._cols);

  for (unsigned i = 0; i < _rows; i++)
    for (unsigned j = 0; j < a._cols; j++)
      for (unsigned k = 0; k < _cols; k++) 
	r[i][j] += (*this)[i][k] * a[k][j];

  return r;
}


Matrix Matrix::operator*(const double a)
{
  Matrix r(_rows, _cols);

  for (unsigned i = 0; i < _rows; i++)
    for (unsigned j = 0; j < _cols; j++)
      r[i][j] = (*this)[i][j] * a;

  return r;
}


Matrix Matrix::transpose() const 
{
  Matrix r(_cols, _rows);

  for (unsigned i = 0; i < _rows; i++)
    for (unsigned j = 0; j < _cols; j++)
      r[j][i] = (*this)[i][j];

  return r;  
}


Matrix Matrix::Minor(const unsigned row, const unsigned col) const
{
  if (row >= 0 && row <= (_rows - 1) && col >= 0 && col <= (_cols - 1))
    {
      Matrix res(_rows - 1, _cols - 1);
    
      for(unsigned r = 0; r < _rows; r++)
	{
	  for(unsigned c = 0; c < _cols; c++)
	    {
	      if(r == row || c == col)
		continue;

	      res[r - (r > row)][c - (c > col)] = _m[r][c];
	    }
	}
  
      return res;
    }
  else
    {
      cout << "Index for minor out of range" << endl;
      exit(1);
    }
}


void Matrix::Write(ostream& s) const 
{
  for (unsigned i = 0; i < _m.size(); i++) 
    {
      for (unsigned j = 0; j < _m[i].size(); j++)
	s << setw(6) << _m[i][j] << " ";
      s << endl;
    }
}

unsigned Matrix::getRowsSize() const
{
  return _m.size();
}
  
unsigned Matrix::getColsSize() const
{
  return _m[0].size();
}


ostream& operator << ( ostream& s, Matrix m) 
{
  m.Write(s);
  return s;
}


Matrix Eye(const int n)
{
  Matrix r(n, n);
  
  for (int i = 0; i < n; i++)
    r[i][i] = 1;

  return r;
}


double Det(const Matrix& a)
{
  double d = 0; 
  unsigned rows = a.getRowsSize();
  unsigned cols = a.getColsSize();

  if (rows == cols)
    {
      if (rows == 1)
	{
	  // Matrix 1 x 1
	  d = a[0][0];
	}
      else if (rows == 2)
	{
	  // Matrix 2 x 2
	  d = a[0][0] * a[1][1] - a[1][0] * a[0][1];
	}
      else
	{
	  // Matrix 3 x 3 or bigger
	  for (unsigned c = 0; c < cols; c++)
	    {
	      Matrix M = a.Minor(0, c);
	      d += pow(-1, c) * a[0][c] * Det(M);
	    }
	}
    }
  else
    {
      cout<< "Matrix must be square!" << endl;
      exit(1);
    }

  return d;
}


void Swap(double& a, double& b)
{
  double temp = a;
  a = b;
  b = temp;
}


Matrix Inv(const Matrix& a)
{
  Matrix res;
  double d = 0;
  unsigned rows = a.getRowsSize();
  unsigned cols = a.getColsSize();

  d = Det(a);

  if (rows == cols && d != 0)
    {
      if (rows == 1)
	{
	  // Matrix 1 x 1
	  res = Matrix(rows, cols);
	  res[0][0] = 1 / a[0][0];
	}
      else if (rows == 2)
	{
	  // Matrix 2 x 2
	  res = Matrix(rows, cols);

	  res[0][0] = a[1][1];
	  res[0][1] = -a[0][1];
	  res[1][0] = -a[1][0];
	  res[1][1] = a[0][0];

	  res = res * (1.0/d);
	}
      else
	{
	  // Matrix 3 x 3 or bigger
	  res = Eye(rows);
	  Matrix ai = a;

	  for (unsigned c = 0; c < cols; c++)
	    {
	      // element (c, c) should be non zero. if not, swap content
	      // of lower rows
	      unsigned r;
	      for (r = c; r < rows && ai[r][c] == 0; r++);

	      if (r != c)
		{
		  // swap rows
		  for (unsigned s = 0; s < cols; s++)
		    {
		      Swap(ai[c][s], ai[r][s]);
		      Swap(res[c][s], res[r][s]);
		    }
		}

	      // eliminate non-zero values on the other rows at column c
	      for (unsigned r = 0; r < rows; r++)
		{
		  if(r != c)
		    {
		      // eleminate value at column c and row r
		      if (ai[r][c] != 0)
			{
			  double f = - ai[r][c] / ai[c][c];

			  // add (f * row c) to row r to eleminate the value
			  // at column c
			  for (unsigned s = 0; s < cols; s++)
			    {
			      ai[r][s] += f * ai[c][s];
			      res[r][s] += f * res[c][s];
			    }
			}
		    }
		  else
		    {
		      // make value at (c, c) one,
		      // divide each value on row r with the value at ai(c,c)
		      double f = ai[c][c];
		      for (unsigned s = 0; s < cols; s++)
			{
			  ai[r][s] /= f;
			  res[r][s] /= f;
			}
		    }
		}
	    }	   
	}
    }
  else
    {
      if (rows == cols)
	{
	  cout << "Determinant of a matrix is zero!" << endl;
	  exit(1);
	}
      else
	{
	  cout<< "Matrix must be square!" << endl;
	  exit(1);
	}
    }

  return res;
}


bool isSymmetric(const Matrix& a)
{
  unsigned rows = a.getRowsSize();
  unsigned cols = a.getColsSize();

  for (unsigned i = 0; i < rows; i++) 
    for (unsigned j = 0; j < cols; j++)
      if(a[i][j] != a[j][i])
	return false;
    
  return true;
}


Matrix uminus(Matrix& a)
{
  unsigned rows = a.getRowsSize();
  unsigned cols = a.getColsSize();

  Matrix r(rows, cols);

  for (unsigned i = 0; i < rows; i++) 
    for (unsigned j = 0; j < cols; j++)
      r[i][j] = -a[i][j];

  return r;      
}
