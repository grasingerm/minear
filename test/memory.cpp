#include "minear.hpp"
#include <iostream>

using namespace minear;
using namespace std;

#define OP_BLOCK if (ops > test_num++)

int main()
{
    const unsigned int ops = 4;
    unsigned int test_num = 0;

    Matrix<double> A(3,3,1);
    OP_BLOCK
    {
        cout << A << endl;
    }
    
    OP_BLOCK
    {
        Matrix<double> B(A);
        cout << B << endl;
    }
    
    OP_BLOCK
    {
        Matrix<double> B(A);
        Matrix<double> C;
        C = A+B;
        A = C;
        
        cout << C << endl;
        cout << A << endl;
    }
    
    OP_BLOCK
    {
        Matrix<double> B(A);
    
        for (unsigned int i = 1; i < 10; i++)
            for (unsigned int j = 1; j < 10; j++)
                B.resize(i,j);
    }
    
    return 0;
}
