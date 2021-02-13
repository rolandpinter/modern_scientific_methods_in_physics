#include "stat.hpp"

std::vector<float> create_random_numbers(size_t N, float lower_limit, float upper_limit)
{
    /// Vector holding the random numbers
    std::vector<float> numbers(N);

    /// Create random float values between lower_limit and upper_limit
    std::random_device rd;  // Only used once to initialise (seed) engine
    std::mt19937 rng(rd()); // Random-number engine used (Mersenne-Twister)
    std::uniform_real_distribution<float> uni(lower_limit, upper_limit); // Create the random distribution

    for(int i = 0; i < (N); ++i)
            numbers[i] = uni(rng); // Sample the random distribution

    return numbers;
}

//------ Class member setter functions ------//
void statistics::calc_mean_sequential()
{
    /// Compute mean
    float sum = std::accumulate(m_data.begin(), m_data.end(), 0.0);
    float mean = sum / std::distance(m_data.begin(), m_data.end());

    /// Set mean
    m_mean_sequential = mean;
}

//------ Class member getter functions ------//
float statistics::mean_sequential(){ return m_mean_sequential;}