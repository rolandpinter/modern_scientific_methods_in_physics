#include "stat.hpp"

int main()
{
    /// Vector holding possible values of N, a.k.a number of data
    std::vector<size_t> N_vec;
    for( int i = 6; i < 26; ++i)
        N_vec.push_back(pow(2, i));

    for(int iN = 0; iN < N_vec.size(); ++iN)
    {
        /// Create a vector filled with random numbers
        size_t N = N_vec[iN];
        float lower_limit = 0.0;
        float upper_limit = 100.0;
        std::vector<float> vec_of_random_numbers = create_random_numbers(N, lower_limit, upper_limit);

        /// Log the init values
        std::cout << "\nSTART: Performing statistical analysis on N = " << N <<
                    " float values in the domain of (" << lower_limit << ", " <<
                    upper_limit << ").\n" << std::endl;

        /// Vectors to hold exection times
        unsigned int N_runs = 10;
        std::vector<float> exec_times_mean_sequential(N_runs);
        std::vector<float> exec_times_mean_parallel(N_runs);
        std::vector<float> exec_times_deviation_sequential(N_runs);
        std::vector<float> exec_times_deviation_parallel(N_runs);

        /// Perform statistical analysis on vec_of_random_number 10 times, to measure execution time precisely
        for(int irun = 0; irun < N_runs; ++irun)
        {
            /// Create a statistics object with the vector holding the random numbers
            statistics stat_object = statistics(vec_of_random_numbers);

            /// Compute mean, deviation sequentially and parallel
            stat_object.calc_mean_sequential();
            stat_object.calc_mean_parallel();
            stat_object.calc_deviation_sequential();
            stat_object.calc_deviation_parallel();
            
            /// Get the computed values
            float mean_seq = stat_object.mean_sequential();
            float mean_par = stat_object.mean_parallel();
            float dev_seq = stat_object.deviation_sequential();
            float dev_par = stat_object.deviation_parallel();
            
            /// Log the values to consol and compare if they are the same or not
            float tolerance = 1e-4;
            std::cout << "\nirun = " << irun << std::endl;
            std::cout << "Mean computed sequentially: " << mean_seq << std::endl;
            std::cout << "Mean computed parallel: " << mean_par << std::endl;
            compare_results(mean_seq, mean_par, tolerance, "mean");

            std::cout << "Deviation computed sequentially: " << dev_seq << std::endl;
            std::cout << "Deviation computed parallel: " << dev_par << std::endl;
            compare_results(dev_seq, dev_par, tolerance, "deviation");

            /// Get the execution times and store them
            exec_times_mean_sequential.push_back(stat_object.exec_time_mean_sequential());
            exec_times_mean_parallel.push_back(stat_object.exec_time_mean_parallel());
            exec_times_deviation_sequential.push_back(stat_object.exec_time_deviation_sequential());
            exec_times_deviation_parallel.push_back(stat_object.exec_time_deviation_parallel());
        }

        /// Compute the average of execution times
        float avg_exec_mean_seq = compute_mean(exec_times_mean_sequential.begin(), exec_times_mean_sequential.end());
        float avg_exec_mean_par = compute_mean(exec_times_mean_parallel.begin(), exec_times_mean_parallel.end());
        float avg_exec_dev_seq = compute_mean(exec_times_deviation_sequential.begin(), exec_times_deviation_sequential.end());
        float avg_exec_dev_par = compute_mean(exec_times_deviation_parallel.begin(), exec_times_deviation_parallel.end());

        /// Append the average execution times and N to the logfile
        std::ofstream logfile;
        logfile.open ("../logfile", std::ios::app);
        logfile << N << "," << avg_exec_mean_seq << "," << avg_exec_mean_par << "," << avg_exec_dev_seq << "," << avg_exec_dev_par << "\n";
        logfile.close();
    }

    return 0;
}