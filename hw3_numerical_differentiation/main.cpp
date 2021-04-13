#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>

// Exact function form
double f(double x, int F, double q, int a, int h){
   return ((F / q) * (cosh(q * x / F) - cosh(q * a * 0.5 / F))) + h;
}

// O(h^6) precise form of the derivative of f based on the Richardson extrapolation
template<typename T_f>
double df(T_f f, double x, double F, double q, int a, int h, double dx){
    return ((128 * (f(x + dx, F, q, a, h) - f(x - dx, F, q, a, h)) -
            24 * (f(x + 2*dx, F, q, a, h) - f(x - 2*dx, F, q, a, h)) +
            1 * (f(x + 4*dx, F, q, a, h) - f(x - 4*dx, F, q, a, h)) ) / 15);
}

int main()
{
    // Given parameters by the exercise
    const int F = 900;    // [F] = N
    const double q = 1.8; // [q] = N/m
    const int a = 200;    // [a] = m
    const int h = 35;     // [h] = m

    // Lower and upper limit of the integral, number of equidistant partitions, dx
    const double int_lower_limit = 0.0;
    const double int_upper_limit = 200.0;
    const int n = 10000;
    double dx = (int_upper_limit - int_lower_limit) / n;
    
    // Vector to hold central x values for "central integral"
    std::vector<double> centrums(n);
    for(int i = 0; i < n; ++i)
        centrums[i] = i * dx + dx/2;

    // Determine critical n for 0.01 error: Something is wrong here, n values are too small...
    /*
    const double M2 = 0.002 * cosh(0.002 * int_upper_limit);
    const double M4 = pow(0.002, 3.0) * cosh(0.002 * int_upper_limit);
    const int n_central = sqrt(M2 * pow((int_upper_limit - int_lower_limit), 3.0) / 0.24);
    const int n_trapesoidal = sqrt(M2 * pow((int_upper_limit - int_lower_limit), 3.0) / 0.12);
    const int n_simpson = pow(M4 * pow((int_upper_limit - int_lower_limit), 5.0) / 28.8, 0.25);
    std::cout << n_central << " " << n_trapesoidal << " " << n_simpson << std::endl;
    */

    // (1) Compute the length of the rope based on the "central integral"
    double M = 0;
    for (int i = 0; i < n; ++i){
        M += sqrt(1 + (df(f, centrums[i], F, q, a, h, dx) * df(f, centrums[i], F, q, a, h, dx)) ) * dx;
    }

    // (2) Compute the length of the rope based on the trapesoidal rule
    double T = 0;
    // First and last terms in the sum are only multiplied with 1, so I'm adding summing them before
    T += sqrt(1 + (df(f, int_lower_limit, F, q, a, h, dx) * df(f, int_lower_limit, F, q, a, h, dx)) );
    T += sqrt(1 + (df(f, int_upper_limit, F, q, a, h, dx) * df(f, int_upper_limit, F, q, a, h, dx)) );
    // All the others terms are multiplied with 2, so a for loop can be written
    for(int i = 1; i < n - 1; ++i){
        T += 2 *  sqrt(1 + (df(f, i*dx, F, q, a, h, dx) * df(f, i*dx, F, q, a, h, dx)) );
    }
    // T is multiplied with dx/2
    T *= (dx/2);

    // (3) Compute the length of the rope based on the 1/3 Simpson
    double S = (2 * M + T) / 3;
    
    // (4) Write out the resultss
    std::cout << "central integral M = " << M << std::endl;
    std::cout << "trapesoidal integral T = " << T << std::endl;
    std::cout << "1/3 Simpson integral S = " << S << std::endl;

    std::ofstream result_file;
    result_file.open("../results.csv");
    result_file << "M,T,S\n";
    result_file << M << "," << T << "," << S;
    result_file.close();

    return 0;
}