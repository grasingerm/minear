#include "../src/minear.hpp"
#include <iostream>

using namespace std;
using namespace minear;

int main()
{
    Matrix<double> a(3,3);
    a << 1.1 << 2.2 << 3.3
      << 0.1 << 0.2 << 0.3
      << 3.1 << 3.2 << 3.3;
    
    Matrix<double> b(a);
    Matrix<double> I(3,3);
    I << 1 << 0 << 0
      << 0 << 1 << 0
      << 0 << 0 << 1;
      
    cout << "a = " << endl << a << endl;
    cout << "a + b = " << endl << a+b << endl;
    cout << "a - b = " << endl << a-b << endl;
    cout << "-a" << endl << -a << endl;
    cout << "a * I" << endl << a*I << endl;
    cout << "I * b" << endl << I*b << endl;
    cout << "a * b" << endl << a*b << endl;
    cout << "b * a" << endl << b*a << endl;
    /*
    for (unsigned int i = 0; i < a.n_rows; i++)
    {
        for (unsigned int j = 0; j < a.n_cols; j++)
            cout << a(i,j) << " ";
        cout << endl;
    }
    */

    return 0;
}
