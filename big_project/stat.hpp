#ifndef stat_hpp
#define stat_hpp

#include <stdio.h>    // for basic IO operations
#include <iostream>   // IO stream
#include <vector>     // for std::vector iterable container
#include <fstream>    // needed for reading in files
#include <string>     // for strings, of course
#include <numeric>    // for algos like std::accumulate
#include <algorithm>  // for more algos
#include <random>     // for random number generation

/// Function to create N random float numbers in a given range (lower_limit, upper_limit)
std::vector<float> create_random_numbers(size_t N, float lower_limit, float upper_limit);

class statistics
{
private:
    float m_mean_sequential;
    float m_mean_parallel;
    
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
    void calc_mean_sequential(); // Compute the mean of m_data in a sequential way

    /// Class member getter functions
    float mean_sequential();     // Return the mean computed in a sequential way
    
};

#endif /* stat_hpp */