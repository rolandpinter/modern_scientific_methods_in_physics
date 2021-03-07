#include <iostream>
#include <cmath>

/*
T_f: type of function
T_df: type of derivative function
T_stop: type of stopping criterion function
T_x0: type of initial x value
T_epsilon: type of epsilon, which will be used for precision
*/
template<typename T_f, typename T_df, typename T_stop, typename T_x0, typename T_epsilon>
T_x0 Newton(T_f f, T_df df, T_stop stopping_crit, T_x0 x0, T_epsilon epsilon)
{
    // Formula for next candidate: x_n+1 = x_n - f(x_n) / f'(x_n)
    T_x0 x1 = x0 - (f(x0) / df(x0));

    // While not converging with enough precision, iterate
    while (stopping_crit(x0, x1, epsilon)){
        x0 = x1;
        x1 = x0 - (f(x0) / df(x0));
    }

    // Return proposed root
    return x1;
}

// Implement functions: dummy function, its derivative, stopping criterion function
double f(double x){ return x*x - 612.0; }
double df(double x) { return 2 * x; }
bool stopping_criterion(double x0, double x1, double epsilon) { return abs(x1 - x0) > epsilon; }

int main()
{
    double x0 = 10.0;                                             // Starting x value
    double epsilon = 1e-3;                                        // Required precision
    double demo = Newton(f, df, stopping_criterion, x0, epsilon); // This should return 24.738633753705963298928 (example from slide)
    double result_from_slide = 24.738633753705963298928;          // Result from lecture slide, for comparision purposes

    if (abs(demo - result_from_slide) < 1e-6) 
        std::cout << "Task completed! :)" << std::endl;
    else 
        std::cout << "Task failed! :(" << std::endl;

    return 0;
}