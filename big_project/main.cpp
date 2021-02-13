#include "stat.hpp"

std::vector<float> create_dummy_vector()
{
    /// Dummy vector just for development phase, testing
    int N = 10;
    std::vector<float> dummy(N);
    for(int i = 0; i < N; ++i)
        dummy[i] = i;
    return dummy;
}

int main(){
    std::vector<float> a = create_random_numbers(10, 0.0, 12.0);
    std::vector<float> dummy = create_dummy_vector();

    statistics foo = statistics(dummy);
    
    for (int i = 0; i < foo.m_data.size(); ++i)
        std::cout << foo.m_data[i] << std::endl;

    std::cout << foo.mean_sequential() << std::endl;
    foo.calc_mean_sequential();
    std::cout << foo.mean_sequential() << std::endl;
}