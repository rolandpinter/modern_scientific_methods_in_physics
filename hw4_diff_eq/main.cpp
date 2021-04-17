#include <fstream> // std::ofstream
#include <vector>  // std::vector
#include <cmath>   // pow
#include <string>  // std::string

// Exact form of f(t_n, y_n) given by the exercise
double f(double value);

// Function to perform Newton method
template<typename T>
std::vector<double> Newton_method(double dt, unsigned int N, double y0, T f);

// Function to perform RK4 method
template<typename T>
std::vector<double> RK4_method(double dt, unsigned int N, double y0, T f);

// Function to dump results to csv file
void dump_results(std::string filename, unsigned int N, double dt, std::vector<double> &Newton_results, std::vector<double> &RK4_results);

int main()
{
    double dt = 1e-4;       // time step-size
    unsigned int N = 10000; // Number of time steps
    double y0 = 0.0;        // Initial value of y(t) at t = t0
    
    // Solve the given differential equation numerically
    std::vector<double> Newton_results = Newton_method(dt, N, y0, f);
    std::vector<double> RK4_results = RK4_method(dt, N, y0, f);

    // Dump results to file
    dump_results("../results.csv", N, dt, Newton_results, RK4_results);

    return 0;
}

// Exact form of f(t_n, y_n) given by the exercise
double f(double value)
{
    return 1 + pow(value, 2.0);
}

// Function to perform Newton method
template<typename T>
std::vector<double> Newton_method(double dt, unsigned int N, double y0, T f)
{
    std::vector<double> Newton_results(N); // Vector to hold Newton method results
    Newton_results[0] = y0;                // t = 0 initial value given as y0

    // Compute Newton method results
    for(unsigned int i = 1; i < N; ++i)
        Newton_results[i] = Newton_results[i - 1] + dt * f(Newton_results[i - 1]);

    // Return the Newton method results
    return Newton_results;
}

// Function to perform RK4 method
template<typename T>
std::vector<double> RK4_method(double dt, unsigned int N, double y0, T f)
{
    std::vector<double> RK4_results(N); // Vector to hold RK4 method restults
    RK4_results[0] = y0;                // t = 0 initial value given as y0

    for(unsigned int i = 1; i < N; ++i){
        double y_prev = RK4_results[i - 1];
        double k1 = f(y_prev);
        double k2 = f(y_prev + (dt * k1 * 0.5));
        double k3 = f(y_prev + (dt * k2 * 0.5));
        double k4 = f(y_prev + (dt * k3));
        RK4_results[i] = y_prev + (dt * (k1 + 2*k2 + 2*k3 + k4) / 6);
    }

    // Return the RK4 results
    return RK4_results;
}

// Function to dump results to csv file
void dump_results(std::string filename, unsigned int N, double dt, std::vector<double> &Newton_results, std::vector<double> &RK4_results)
{
    // Open output file
    std::ofstream result_file;
    result_file.open(filename);

    // Write header row
    result_file << "t,Newton_results,RK4_results\n";

    // Write the results
    for(unsigned int i = 0; i < N; ++i)
        result_file << i * dt<< "," << Newton_results[i] << "," << RK4_results[i] << "\n";

    // Close the file
    result_file.close();
}