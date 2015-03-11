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
    cout << "2.0 * a" << endl << 2.0*a << endl;
    cout << "a * 2.0" << endl << a*2.0 << endl;
    
    cout << "Printing 'a' with range-based for loop" << endl;
    for (auto& a_i : a)
        cout << a_i << endl;

    return 0;
}
