#include <vector>
#include "methods.hpp"

using namespace std;

int main()
{
  double alpha;
  unsigned n;         
  unsigned izbor; 
  unsigned maxIter;
  double tol;

  cout << "Enter the dimension of a square matrix: " << endl;
  cin >> n;

  Matrix A(n,n);

  cout << "Enter the elements of a square matrix A:" << endl;

  for(unsigned i = 0; i < n; i++)
    for(unsigned j = 0; j < n; j++)
      cin >> A[i][j];

  cout << "Enter vector b" << endl;

  Matrix b(3,1);

  for(unsigned i = 0; i < n; i++)
    cin >> b[i][0];

  cout << "Enter the starting point" << endl;

  Matrix X(3,1);
  
  for(unsigned i = 0; i < n; i++)
    cin >> X[i][0];

  cout << "Enter tol" << endl;
  cin >> tol;

  cout << "Enter the max number of iterations" << endl;
  cin >> maxIter;
  
  cout << "Select one of the methods:" << endl;
  cout << "(0) - Conjugate Gradient Method" << endl;
  cout << "(1) - Gradient Descent Method" << endl;
  cout << "(2) - Gradient Descent With Fixed Step Size" << endl;

  cin >> izbor;

  switch(izbor)
    {
    case 0:
      cout << ConjugateGradientMethod(A, b, X, tol, maxIter) << endl;
      break;

    case 1:
      cout << GradientDescentMethod(A, b, X, tol, maxIter) << endl;
      break;
	
    case 2:
      cout << "Enter alpha: " << endl;
      cin >> alpha;
      cout << GradientDescentWithFixedStepSize(A, b, X, tol, maxIter, alpha) << endl;
      break;

    default:
      cout << "You didn't enter one of the offered numbers." << endl;
      break;
    }
  
  return 0;
}
