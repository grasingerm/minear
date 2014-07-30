#include "minear.hpp"
#include "debug.hpp"
#include <armadillo>
#include <cassert>

using namespace arma;
using namespace std;

int main()
{
    const int max_iters = 1000;
    int outter_a, inner, outter_b;
    mat arma_A, arma_B, arma_C, mult_result_arma, add_result_arma;
    minear::Matrix<double> min_A, min_B, min_C, mult_result_min, add_result_min;
    
    cout << "Max iterations: " << max_iters << endl;
    cout << "Starting tests..." << endl;
    
    for (unsigned int i = 0; i < max_iters; i++)
    {
        cout << endl << "iter " << i+1 << endl;
        cout << "-----------------------------" << endl;
        outter_a = rand() % 100 + 1;
        inner = rand() % 100 + 1;
        outter_b = rand() % 100 + 1;
        
        arma_A = mat(outter_a, inner);
        arma_A.randn();
        
        arma_B = mat(inner, outter_b);
        arma_B.randu();
        
        arma_C = mat(outter_a, inner);
        arma_C.randu();
        
        cout << "resizing" << endl;
        min_A.resize(outter_a, inner);
        min_B.resize(inner, outter_b);
        min_C.resize(outter_a, inner);
        
        cout << "copying" << endl;
        for (unsigned int i = 0; i < outter_a; i++)
            for (unsigned int j = 0; j < inner; j++)
                min_A(i,j) = arma_A(i,j);
                
        for (unsigned int i = 0; i < inner; i++)
            for (unsigned int j = 0; j < outter_b; j++)
                min_B(i,j) = arma_B(i,j);
                
        for (unsigned int i = 0; i < outter_a; i++)
            for (unsigned int j = 0; j < inner; j++)
                min_C(i,j) = arma_C(i,j);
        
        cout << "computations" << endl;
        
        cout << "multiply" << endl;
        mult_result_arma = arma_A*arma_B;
        mult_result_min = min_A*min_B;
        for (unsigned int i = 0; i < mult_result_arma.n_rows; i++)
            for (unsigned int j = 0; j < mult_result_arma.n_cols; j++)
                ASSERT_NEAR(mult_result_min(i,j), mult_result_arma(i,j), 1e-3);
        
        cout << "add" << endl;
        add_result_arma = arma_A+arma_C;
        add_result_min = min_A+min_C;
        for (unsigned int i = 0; i < add_result_arma.n_rows; i++)
            for (unsigned int j = 0; j < add_result_arma.n_cols; j++)
                ASSERT_NEAR(add_result_min(i,j), add_result_arma(i,j), 1e-3);
        
        cout << "subtract" << endl;
        add_result_arma = arma_A-arma_C;
        add_result_min = min_A-min_C;
        for (unsigned int i = 0; i < add_result_arma.n_rows; i++)
            for (unsigned int j = 0; j < add_result_arma.n_cols; j++)
                ASSERT_NEAR(add_result_min(i,j), add_result_arma(i,j), 1e-3);
        
        cout << "subtract" << endl;
        add_result_arma = arma_C-arma_A;
        add_result_min = min_C-min_A;
        for (unsigned int i = 0; i < add_result_arma.n_rows; i++)
            for (unsigned int j = 0; j < add_result_arma.n_cols; j++)
                ASSERT_NEAR(add_result_min(i,j), add_result_arma(i,j), 1e-3);
                
        cout << "subtract" << endl;
        add_result_arma = arma_C-arma_C;
        add_result_min = min_C-min_C;
        for (unsigned int i = 0; i < add_result_arma.n_rows; i++)
            for (unsigned int j = 0; j < add_result_arma.n_cols; j++)
                ASSERT_NEAR(add_result_min(i,j), add_result_arma(i,j), 1e-3);
    }
    
    cout << "... tests complete." << endl;

    return 0;
}
