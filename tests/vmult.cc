#include <type_traits>
#include <cstdlib>
#include <cmath>
#include <cstdint>
#include <array>
#include <cassert>
#include <vector>
#include <limits>
#include <iostream>

#include "../include/constexpr_math.h"
#include "../include/constexpr_array.h"
#include "../include/la_operations.h"
#include "../include/constexpr_quadrature.h"
#include "../include/polynomialbasis/constexpr_lagrange.h"
#include "../include/vmult.h"

using namespace std;

// Hardcode solution
template <typename y_type, size_t order>
constexpr_array < constexpr_array < y_type, order + 1 >, order + 1 > lagrange_nodes(constexpr_array < constexpr_array < y_type, order + 1 >, order + 1 > u, constexpr_array < y_type, order + 1 > q_weights) {
  for (unsigned int i = 0; i < q_weights.size(); i++) {
    for (unsigned int j = 0; j < q_weights.size(); j++) {
      u[i][j] *= q_weights[i] * q_weights[j];
    }
  }
  return u;
}

template <typename y_type, size_t size>
constexpr_array<y_type, size> create_vector()
{
  constexpr_array<y_type, size> arr{1.};
  for (unsigned int i = 0; i < size; ++i)
    arr[i] = i;
  return arr;
}

template <typename y_type, size_t size>
constexpr_array<constexpr_array<y_type, size>, size> create_array()
{
  constexpr_array<constexpr_array<y_type, size>, size> arr;
  for (unsigned int i = 0; i < size; ++i)
    for (unsigned int j = 0; j < size; ++j)
      arr[i][j] = 1;
  return arr;
}


int main()
{
  // Initialize VMULT
  constexpr size_t order = 3;
  constexpr size_t q_order = 3;
  constexpr VMULT<long double, order, q_order, Quadrature , Lagrange > vmult;

  // Compute VMULT Mass Matrix
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > u_1 = create_array < long double, order + 1 > ();
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > y_1 = create_array < long double, order + 1 > ();
  vmult.mass(y_1, u_1);

  // Compute VMULT Gradient
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > u_2 = create_array < long double, order + 1 > ();
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > y_2 = create_array < long double, order + 1 > ();
  vmult.gradient(y_2, u_2);

  // Compute VMULT Laplacian
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > u_3 = create_array < long double, order + 1 > ();
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > y_3 = create_array < long double, order + 1 > ();
  vmult.laplacian(y_3, u_3);

  // Output resulting vector y.
  for (unsigned int i = 0; i < order + 1; i++) {
    for (unsigned int j = 0; j < order + 1; j++) {
      std::cout << "y[" << i  << "," << j << "] = " << y_1[i][j] << endl;
    }
  }


  /** TESTING **/

  
  // Hardcode solution
  Quadrature<long double,order> quad;
  constexpr_array < constexpr_array < long double, order + 1 >, order + 1 > y_hard = lagrange_nodes<long double, order>(u_1, quad.weights_);

  // Testing for correctness
  for (unsigned int i = 0; i < order + 1; i++) {
    for (unsigned int j = 0; j < order + 1; j++) {
      assert(y_1[i][j] == y_hard[i][j]);
    }
  }

  // Testing for correct complexity

  cout << "Testing was succesful." << endl;
  

  return 0;
}