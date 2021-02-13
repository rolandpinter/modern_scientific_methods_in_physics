#include "stat.hpp"

int main()
{
    /// Create a vector filled with random numbers
    size_t N = 16777216; // 8^8
    float lower_limit = 0.0;
    float upper_limit = 12.0;
    std::vector<float> vec_of_random_numbers = create_random_numbers(N, lower_limit, upper_limit);

    /// Log the init values
    std::cout << "\nSTART: Performing statistical analysis on N = " << N <<
                 " float values in the domain of (" << lower_limit << ", " <<
                 upper_limit << ").\n" << std::endl;

    /// Create a statistics object with the vector holding the random numbers
    statistics stat_object = statistics(vec_of_random_numbers);

    /// Compute mean sequentially and parallel
    stat_object.calc_mean_sequential();
    stat_object.calc_mean_parallel();
    
    /// Get the computed mean values
    float mean_seq = stat_object.mean_sequential();
    float mean_par = stat_object.mean_parallel();

    /// Log the mean values to consol and compare if they are the same or not
    std::cout << "Mean computed sequentially: " << mean_seq << std::endl;
    std::cout << "Mean computed parallel: " << mean_par << std::endl;

    float tolerance = 1e-3;
    compare_results(mean_seq, mean_par, tolerance, "mean");

}