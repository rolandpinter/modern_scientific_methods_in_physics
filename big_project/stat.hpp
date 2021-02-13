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

std::vector<float> create_random_numbers(size_t N, float lower_limit, float upper_limit);


#endif /* stat_hpp */