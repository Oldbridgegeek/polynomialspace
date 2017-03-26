#include <type_traits>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <array>
#include <vector>
#include <limits>
#include <cassert>
#include <type_traits>
#include <iostream>

#include "../../include/constexpr_math.h"
#include "../../include/constexpr_array.h"
#include "../../include/constexpr_quadrature.h"
#include "../../include/polynomialbasis/constexpr_lagrange.h"


// Epsilon for asserting
constexpr long double eps = 0.00000001;

// Order for Interpolation
constexpr static size_t order = 3;


int main() {

    /** TEST CONSTEXPR **/
    constexpr Lagrange<long double, order, Quadrature> lagr;
    /** lagr object is known at compile time **/


    /** TEST EVAL LAGRANGE **/

    // If we evaluate at node points we expect 1
    for (unsigned int i = 0; i < order + 1; i++) {
        assert( abs(lagr.eval_lagrange(lagr.knots_[i], i)-1) <= eps);
    }

    // If we evalute the i-th lagrange polynomial at node j-th node point we except 0
    for (unsigned int j = 0; j < order + 1 ; j++) {
        for (unsigned int i = 0; i < order + 1; i++) {
            if ( i != j ) {
                assert( abs(lagr.eval_lagrange(lagr.knots_[i], j)) <= eps);
            }
        }
    }

    /** TEST EVAL GRADIENT LAGRANGE **/
    // 1st Lagrange Basis 
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[0],0) + 6) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[1],0) + 1.61804) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[2],0) - 0.618034) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[3],0) + 1) <= eps );
    // 2nd Lagrange Basis
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[0],1) - 8.09017) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[1],1) - 0.00004) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[2],1) + 2.23611) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[3],1) - 3.09007) <= eps );
    // 3rd Lagrange Basis
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[0],2) + 3.09017) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[1],2) - 2.23607) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[2],2) - 0.00004) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[3],2) + 8.09007) <= eps );
    // 4th Lagrange Basis
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[0],3) - 1) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[1],3) + 0.618034) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[2],3) - 1.61804) <= eps );
    assert( abs(lagr.eval_1st_derivative(lagr.knots_[3],3) - 6) <= eps );




    return 0;
}
