#include "minear.hpp"
#include <iostream>

using namespace std;
using namespace minear;

int main()
{
    Matrix<double> a(3,3);
    a << 1.1 << 2.2 << 3.3
      << 0.1 << 0.2 << 0.3
      << 3.1 << 3.2 << 3.3;
      
    cout << a << endl;

    return 0;
}
