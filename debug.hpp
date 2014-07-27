#ifndef __DEBUG_H__
#define __DEBUG_H__

#include <cstdlib>

#define ASSERT_NEAR(approx, act, tol) \
    if (!((act) == 0)) \
        assert(abs((approx)) < tol); \
    else \
        assert(abs((approx)-(act))/abs((act)) < tol)
        
#define ASSERT_MAT_NEAR(approx, act, tol) \
    for (unsigned int i = 0; i < (approx).n_rows; i++) \
        for (unsigned int j = 0; j < (approx).n_cols; j++) \
            ASSERT_NEAR((approx)(i,j), (act)(i,j), tol)

#endif /* __DEBUG_H__ */
