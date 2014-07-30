#include <iostream>
#include <array>
#include "minear.hpp"

using namespace std;
using namespace minear;

int main()
{
    Matrix<double> z(4,4,1);
    cout << z << endl;
    
    Matrix<double> x(4,1,1);
    cout << x << endl;
    
    cout << z*x << endl;
    
    return 0;
}
