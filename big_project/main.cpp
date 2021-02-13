#include "stat.hpp"

int main(){
    std::vector<float> a = create_random_numbers(10, 0.0, 12.0);

    for(int i = 0; i < a.size(); ++i)
        std::cout << a[i] << std::endl;
}