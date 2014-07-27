#include "../minear.hpp"
#include "../debug.hpp"
#include <armadillo>
#include <cassert>

using namespace arma;
using namespace std;

int main()
{
    const int max_iters = 1000;
    int outter_a, inner, outter_b;
    mat A, B, E;
    minear::Matrix<double> C, D, F;
    
    cout << "Max iterations: " << max_iters << endl;
    cout << "Starting tests..." << endl;
    
    for (unsigned int i = 0; i < max_iters; i++)
    {
        outter_a = rand() % 100 + 1;
        inner = rand() % 100 + 1;
        outter_b = rand() % 100 + 1;
        
        A = mat(outter_a, inner);
        A.randn();
        
        B = mat(inner, outter_b);
        B.randu();
        
        C.resize(outter_a, inner);
        D.resize(inner, outter_b);
        
        for (unsigned int i = 0; i < outter_a; i++)
            for (unsigned int j = 0; j < inner; j++)
                C(i,j) = A(i,j);
                
        for (unsigned int i = 0; i < inner; i++)
            for (unsigned int j = 0; j < outter_b; j++)
                D(i,j) = B(i,j);
        
        E = A*B;
        F = C*D;
        ASSERT_MAT_NEAR(F, E, 1e-5);
        
        E = A+B;
        F = C+D;
        ASSERT_MAT_NEAR(F, E, 1e-5);
        
        E = A-B;
        F = C-D;
        ASSERT_MAT_NEAR(F, E, 1e-5);
        
        E = B-A;
        F = C-D;
        ASSERT_MAT_NEAR(F, E, 1e-5);
    }
    
    cout << "... tests complete." << endl;

    return 0;
}
