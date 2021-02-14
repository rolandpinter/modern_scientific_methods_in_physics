#include "stat.hpp"

//------------------ Helper functions ------------------//

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

float compute_sum(std::vector<float>::iterator it_start, std::vector<float>::iterator it_end)
{
    return std::accumulate(it_start, it_end, 0.0);
}

float compute_mean(std::vector<float>::iterator it_start, std::vector<float>::iterator it_end)
{
    return compute_sum(it_start, it_end) / std::distance(it_start, it_end);
}

void compare_results(float result_sequential, float result_parallel, float tolerance, std::string type_of_result)
{
    float relative_error = std::abs((result_sequential - result_parallel) / result_sequential);

    std::cout << "###############################" << std::endl;
    std::cout << "Relative error for " << type_of_result << " is: " << relative_error << std::endl;
    if( relative_error < tolerance ) std::cout << type_of_result <<" calculation OK!" << std::endl;
    else std::cout << type_of_result <<" calculation WRONG!" << std::endl;
    std::cout << "###############################\n" << std::endl;
}

//------------------ Class member setter functions ------------------//

void statistics::calc_mean_sequential()
{
    /// Record start time
    auto start_time = std::chrono::high_resolution_clock::now();

    /// Compute and set the mean
    m_mean_sequential = compute_mean(m_data.begin(), m_data.end());;

    /// Record end time
    auto end_time = std::chrono::high_resolution_clock::now();

    /// Compute elapsed time
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Sequential mean for N = " << m_data.size() << " float elements took " << elapsed_time << " microseconds!"<< std::endl; 
}

void statistics::calc_mean_parallel()
{
    /// Record start time
    auto start_time = std::chrono::high_resolution_clock::now();

    /// Determine how many threads are supported by the host
    int possible_number_of_threads = (int)std::thread::hardware_concurrency();

    /// Create futures for the possible number of threads
    std::vector<std::future<float> > futures(possible_number_of_threads);

    /// Launch parallel threads to compute means of parts of the data
    for(int n = 0; n < possible_number_of_threads; ++n)
    {
        // Divide the whole interval into sub parts
        std::vector<float>::iterator it0 = m_data.begin() + n * m_data.size() / possible_number_of_threads;
        std::vector<float>::iterator it1 = m_data.begin() + (n + 1) * m_data.size() / possible_number_of_threads;

        // Compute the mean of the sub parts
        futures[n] = std::async( std::launch::async, compute_mean, it0, it1);
    }

    /// Collect the parallel results
    float sum_of_means = std::accumulate(futures.begin(), futures.end(), 0.0,
                                        [](float acc_value, std::future<float>& f){ return acc_value + f.get();});

    /// Divide the sum of means with the number of possible threads to get the actual mean
    float mean = sum_of_means / possible_number_of_threads;

    /// Set the mean
    m_mean_parallel = mean;

    /// Record end time
    auto end_time = std::chrono::high_resolution_clock::now();

    /// Compute elapsed time
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Parallel mean for N = " << m_data.size() << " float elements with " << possible_number_of_threads << " threads took "
              << elapsed_time << " microseconds!"<< std::endl; 
}

void statistics::calc_deviation_sequential()
{
    // Formula: SQRT[sum{ (x - mean)**2 } / N-1]
    // I will transform this problem to a mean calculation problem
    // - I will transform the data as: x --> (x - mean)**2
    // - then calc the mean of it: (x - mean)**2 --> (x - mean)**2 / N - 1
    // As a last step, take the square root: (x - mean)**2 / N  - 1 --> sqrt((x - mean)**2 / N - 1)

    /// Record start time
    auto start_time = std::chrono::high_resolution_clock::now();

    /// Vector to hold transformed data
    size_t N = m_data.size();
    std::vector<float> transformed_data (N);

    /// Access already computed mean of the data
    float mean = statistics::mean_sequential();

    /// Transform the data as discussed above
    std::transform(m_data.begin(), m_data.end(), transformed_data.begin(), 
                   [&](float x){ return (x - mean ) * (x - mean );});
    
    /// Compute the mean of the transformed data (a.k.a. we get the variance of the data)
    float sum = compute_sum(transformed_data.begin(), transformed_data.end());
    float variance = sum / (N - 1); 

    /// Take the square root of the variance and store the deviation
    m_deviation_sequential = sqrt(variance);

    /// Record end time
    auto end_time = std::chrono::high_resolution_clock::now();

    /// Compute elapsed time
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Sequential deviation for N = " << N << " float elements took " << elapsed_time << " microseconds!"<< std::endl;
}

void statistics::calc_deviation_parallel()
{
    /// Record start time
    auto start_time = std::chrono::high_resolution_clock::now();

    /// Determine how many threads are supported by the host
    int possible_number_of_threads = (int)std::thread::hardware_concurrency();

    /// Create futures for the possible number of threads
    std::vector<std::future<float> > futures(possible_number_of_threads);

    /// Vector to hold transformed data
    size_t N = m_data.size();
    std::vector<float> transformed_data (N);

    /// Access already computed mean of the data
    float mean = statistics::mean_sequential();

    /// Transform the data as discussed above
    std::transform(m_data.begin(), m_data.end(), transformed_data.begin(), 
                   [&](float x){ return (x - mean ) * (x - mean );});

    /// Launch parallel threads to compute sums of parts of the transformed data
    for(int n = 0; n < possible_number_of_threads; ++n)
    {
        // Divide the whole interval into sub parts
        std::vector<float>::iterator it0 = transformed_data.begin() + n * N / possible_number_of_threads;
        std::vector<float>::iterator it1 = transformed_data.begin() + (n + 1) * N / possible_number_of_threads;

        // Compute the mean of the sub parts
        futures[n] = std::async( std::launch::async, compute_sum, it0, it1);
    }

    /// Collect the parallel results
    float sum_of_futures = std::accumulate(futures.begin(), futures.end(), 0.0,
                                        [](float acc_value, std::future<float>& f){ return acc_value + f.get();});

    /// Compute variance
    float variance = sum_of_futures / (N - 1);

    /// Compute deviation
    m_deviation_parallel = sqrt(variance);

    /// Record end time
    auto end_time = std::chrono::high_resolution_clock::now();

    /// Compute elapsed time
    auto elapsed_time = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time).count();
    std::cout << "Parallel deviation for N = " << N << " float elements with " << possible_number_of_threads << " threads took "
              << elapsed_time << " microseconds!"<< std::endl; 
}
//------------------ Class member getter functions ------------------//

float statistics::mean_sequential(){ return m_mean_sequential;}
float statistics::mean_parallel(){ return m_mean_parallel;}
float statistics::deviation_sequential(){ return m_deviation_sequential;}
float statistics::deviation_parallel(){ return m_deviation_parallel;}