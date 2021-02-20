#ifndef stat_hpp
#define stat_hpp

#include <stdio.h>    // for basic IO operations
#include <iostream>   // IO stream
#include <fstream>    // for logfile writing
#include <vector>     // for std::vector iterable container
#include <numeric>    // for algos like std::accumulate
#include <algorithm>  // for more algos
#include <random>     // for random number generation
#include <future>     // for sync threads
#include <chrono>     // for time measurement
#include <string>     // for strings
#include <cmath>      // for sqrt()

/// Function to create N random float numbers in a given range (lower_limit, upper_limit)
std::vector<float> create_random_numbers(size_t N, float lower_limit, float upper_limit);

/// Function to compute sum and mean
float compute_sum(std::vector<float>::iterator it_start, std::vector<float>::iterator it_end);
float compute_mean(std::vector<float>::iterator it_start, std::vector<float>::iterator it_end);

/// Function to compare results, check if they are within tolerated epsilon range
void compare_results(float result_sequential, float result_parallel, float tolerance, std::string type_of_result);

/// Statistics class
class statistics
{
private:
    float m_mean_sequential;
    float m_mean_parallel;
    float m_deviation_sequential;
    float m_deviation_parallel;

    float m_execution_time_mean_sequential;      // in microseconds
    float m_execution_time_mean_parallel;        // in microseconds
    float m_execution_time_deviation_sequential; // in microseconds
    float m_execution_time_deviation_parallel;   // in microseconds
    
public:
    std::vector<float> m_data;

    // Default constructor
    statistics() {}
    
    // Constructor based on argument list
    statistics(std::vector<float> given_data)
    {
        m_data = given_data;
    };
    
    /// Class member setter functions
    void calc_mean_sequential();      // Compute the mean of m_data in a sequential way
    void calc_mean_parallel();        // Compute the mean of m_data in a parallel way
    void calc_deviation_sequential(); // Compute the deviation of m_data in a sequential way
    void calc_deviation_parallel();   // Compute the deviation of m_data in a parallel way

    /// Class member getter functions
    float mean_sequential();      // Return m_mean_sequential
    float mean_parallel();        // Return m_mean_parallel
    float deviation_sequential(); // Return m_deviation_sequential
    float deviation_parallel();   // Return m_deviation_parallel

    float exec_time_mean_sequential(); // Return m_execution_time_mean_sequential
    float exec_time_mean_parallel(); // Return m_execution_time_mean_parallel
    float exec_time_deviation_sequential(); // Return m_execution_time_deviation_sequential
    float exec_time_deviation_parallel(); // Return m_execution_time_deviation_parallel
};

#endif /* stat_hpp */