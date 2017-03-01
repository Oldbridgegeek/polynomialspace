#ifndef __POLYNOMIAL_H__
#define __POLYNOMIAL_H__

// Define function that transforms a vector to an array


template <int order, typename y_type>
class Polynomial {
public:

    constexpr y_type eval_lagr(int i, y_type x, std::array<y_type,order+1> & knots) const {
        y_type val = 1.;
        for (int j = 0; j <= order; j++) {
            if (i != j) {
                val *= (x - knots[j]) / (knots[i] - knots[j]);
            }
        }
        return val;
    }

};

#endif